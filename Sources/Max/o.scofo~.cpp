#include <ext.h>		    // standard Max include, always required (except in Jitter)
#include <ext_obex.h>		// required for "new" style objects
#include <z_dsp.h>		    // required for MSP objects
#include <ext_common.h>

#include "../OScofo.hpp"

#include <algorithm>
#include <fstream>
#include <math.h>

static t_class *oscofo_class = NULL;


typedef struct _oscofo {
	t_pxobject		ob;			// the object itself (t_pxobject in MSP instead of t_object)
	double			offset; 	// the value of a property of our object
	t_clock *Clock;
    OScofo::OScofo *OpenScofo;
	int Event;
	float Tempo;
	int EventIndex;
	bool Following;
	std::string PatchDir;

	// Position
	int CurrentEvent;
	bool ScoreLoaded;

	// Audio
	std::vector<double> inBuffer;
	int FFTSize;
	int HopSize;
	int BlockSize;
	int BlockIndex;
	int Sr;

	// Outlet
	void *EventOut;
	void *TempoOut;
	void *KappaOut;
} t_oscofo;

static void oscofo_score(t_oscofo *x, t_symbol *s){
    x->ScoreLoaded = false;
	bool WasFollowing = x->Following;
	x->Following = false;
    std::string CompletePath = x->PatchDir;
    CompletePath += "/";
    CompletePath += s->s_name;
    std::ifstream file(CompletePath);
    if (!file) {
        object_error((t_object *)x, "[o.scofo~] Score file not found");
        return;
    }
    bool ok;
    try {
        ok = x->OpenScofo->ParseScore(CompletePath.c_str());
    } catch (std::exception &e) {
        object_error((t_object *)x, "[o.scofo~] Error parsing score, %s.", e.what());
        return;
    }
    
	x->ScoreLoaded = true;
	object_post((t_object *)x, "[o.scofo~] Score loaded");
}

// this method is called when the object is created
static void oscofo_set(t_oscofo *x, t_symbol *s, long argc, t_atom *argv)
{
    if (argv[0].a_type != A_SYM) {
        object_error((t_object *)x, "[o.scofo~] First argument must be a symbol");
		outlet_float(x->EventOut, 230);
        return;
    }

    std::string method = atom_getsym(argv)->s_name;
    if (method == "sigma") {
		float sigma = atom_getfloat(argv + 1);
        x->OpenScofo->SetPitchTemplateSigma(sigma);
        object_post((t_object *)x, "Sigma set to %f", sigma);
    } else if (method == "harmonics") {
		long harmonics = atom_getlong(argv + 1);
        x->OpenScofo->SetHarmonics(harmonics);
        object_post((t_object *)x, "Using pitch template with %d harmonics", harmonics);
    } else if (method == "threshold") {
        double dB = atom_getfloat(argv + 1);
        x->OpenScofo->SetdBTreshold(dB);
        object_post((t_object *)x, "Treshold set to %f", atom_getfloat(argv + 1));
    } else if (method == "tunning") {
		float tunning = atom_getfloat(argv + 1);
        x->OpenScofo->SetTunning(tunning);
		object_post((t_object *)x, "Tunning set to %f", tunning);	
    } else if (method == "event") {
		long f = atom_getlong(argv + 1);
        x->CurrentEvent = f;
        x->OpenScofo->SetCurrentEvent(f);
    } else {
        object_error((t_object *)x, "[follower~] Unknown method");
    }
    
}

static void oscofo_following(t_oscofo *x, long f) {
	if (!x->OpenScofo->ScoreIsLoaded()) {
		object_error((t_object *)x, "[o.scofo~] Score not loaded");
		return;
	}
	if (f == 1) {
		x->Following = true;
		object_post((t_object *)x, "Following!");
	} else {
		object_post((t_object *)x, "Not Following!");
		x->Following = false;
	}
}

static void oscofo_start(t_oscofo *x) {
	x->Following = false;
	if (!x->OpenScofo->ScoreIsLoaded()) {
        object_error((t_object *)x, "[o.scofo~] Score not loaded");
        return;
    }
    x->CurrentEvent = -1;
    x->OpenScofo->SetCurrentEvent(-1);
    outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventOut, 0);
    x->Following = true;
}



// this is the tick method for the clock
static void oscofo_tick(t_oscofo *x) {
    if (x->Event != 0) {
		outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
		outlet_float(x->EventOut, x->Event);
    }
}


// this is the 64-bit perform method audio vectors
static void oscofo_perform64(t_oscofo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	if (!x->OpenScofo->ScoreIsLoaded() || !x->Following) {
		return;
    }

	x->BlockIndex += sampleframes;
    std::copy(x->inBuffer.begin() + sampleframes, x->inBuffer.end(), x->inBuffer.begin());
    std::copy(ins[0], ins[0] + sampleframes, x->inBuffer.end() - sampleframes);
	if (x->BlockIndex != x->HopSize) {
		return;
	}

	x->BlockIndex = 0;
    bool ok = x->OpenScofo->ProcessBlock(x->inBuffer);
    if (!ok) {
        return;
    }
    int Event = x->OpenScofo->GetEventIndex();
    if (Event == 0) {
        return;
    }
    if (Event != x->Event) {
        x->Event = Event;
        clock_delay(x->Clock, 0);
    }
}



// registers a function for the signal chain in Max
static void oscofo_dsp64(t_oscofo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->BlockSize = maxvectorsize;
    x->BlockIndex = 0;
    x->inBuffer.resize(x->FFTSize, 0.0f);
	object_method(dsp64, gensym("dsp_add64"), x, oscofo_perform64, 0, NULL);
}


static void *oscofo_new(t_symbol *s, long argc, t_atom *argv){
	t_oscofo *x = (t_oscofo *)object_alloc(oscofo_class);
	if (!x) {
		object_error((t_object *)x, "[o.scofo~] Error creating object");
		return nullptr;
	}
	dsp_setup((t_pxobject *)x, 1);	// MSP inlets: arg is # of inlets and is REQUIRED!
	
	x->TempoOut = outlet_new(x, "float");	// tempo outlet
	x->EventOut = outlet_new(x, "int");
	x->offset = 0.0;
	x->Clock = clock_new(x, (method)oscofo_tick);
	x->FFTSize = 4096;
	x->HopSize = 512;
	x->Sr = sys_getsr();
	x->Following = false;
	x->Event = -1;
	
	char patch_path[MAX_PATH_CHARS];
	short path_id = path_getdefault();
	path_toabsolutesystempath(path_id, NULL, patch_path);
	x->PatchDir = patch_path;

	object_post((t_object *)x, "[o.scofo~] Sr: %d | FFTSize: %d | HopSize: %d", x->Sr, x->FFTSize, x->HopSize);
	//
	x->OpenScofo = new OScofo::OScofo(x->Sr, x->FFTSize, x->HopSize);
	return (x);
}


static void oscofo_free(t_oscofo *x)
{
	delete x->OpenScofo;
}

void ext_main(void *r){
	t_class *c = class_new("o.scofo~", (method)oscofo_new, (method)dsp_free, (long)sizeof(t_oscofo), 0L, A_GIMME, 0);

	// message methods
	class_addmethod(c, (method)oscofo_set, "set", A_GIMME, 0);
	class_addmethod(c, (method)oscofo_score, "score", A_SYM, 0);
	class_addmethod(c, (method)oscofo_following, "follow", A_LONG, 0);
	class_addmethod(c, (method)oscofo_start, "start", A_NOTHING, 0);

	// dsp methods
	class_addmethod(c, (method)oscofo_dsp64, "dsp64", A_CANT, 0);

	// register the class
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	oscofo_class = c;
}
#include <ext.h>		    // standard Max include, always required (except in Jitter)
#include <ext_obex.h>		// required for "new" style objects
#include <z_dsp.h>		    // required for MSP objects


typedef struct _oscofo {
	t_pxobject		ob;			// the object itself (t_pxobject in MSP instead of t_object)
	double			offset; 	// the value of a property of our object
} t_oscofo;


// method prototypes
void *oscofo_new(t_symbol *s, long argc, t_atom *argv);
void oscofo_free(t_oscofo *x);
void oscofo_assist(t_oscofo *x, void *b, long m, long a, char *s);
void oscofo_float(t_oscofo *x, double f);
void oscofo_dsp64(t_oscofo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void oscofo_perform64(t_oscofo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);


// global class pointer variable
static t_class *oscofo_class = NULL;


//***********************************************************************************************

void ext_main(void *r){
	// object initialization, note the use of dsp_free for the freemethod, which is required
	// unless you need to free allocated memory, in which case you should call dsp_free from
	// your custom free function.
	t_class *c = class_new("o.scofo~", (method)oscofo_new, (method)dsp_free, (long)sizeof(t_oscofo), 0L, A_GIMME, 0);
	class_addmethod(c, (method)oscofo_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)oscofo_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)oscofo_assist, "assist",	A_CANT, 0);
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	oscofo_class = c;
}


void *oscofo_new(t_symbol *s, long argc, t_atom *argv){
	t_oscofo *x = (t_oscofo *)object_alloc(oscofo_class);
	if (x) {
		dsp_setup((t_pxobject *)x, 1);	// MSP inlets: arg is # of inlets and is REQUIRED!
		// use 0 if you don't need inlets
		outlet_new(x, nullptr); 		// signal outlet (note "signal" rather than NULL)
		x->offset = 0.0;
	}
	return (x);
}


// NOT CALLED!, we use dsp_free for a generic free function
void oscofo_free(t_oscofo *x)
{
	;
}


void oscofo_assist(t_oscofo *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		//sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		//sprintf(s, "I am outlet %ld", a);
	}
}


void oscofo_float(t_oscofo *x, double f)
{
	x->offset = f;
}


// registers a function for the signal chain in Max
void oscofo_dsp64(t_oscofo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	// when I turn on the sound.
	post("my sample rate is: %f", samplerate);

	// instead of calling dsp_add(), we send the "dsp_add64" message to the object representing the dsp chain
	// the arguments passed are:
	// 1: the dsp64 object passed-in by the calling function
	// 2: the symbol of the "dsp_add64" message we are sending
	// 3: a pointer to your object
	// 4: a pointer to your 64-bit perform method
	// 5: flags to alter how the signal chain handles your object -- just pass 0
	// 6: a generic pointer that you can use to pass any additional data to your perform method

	object_method(dsp64, gensym("dsp_add64"), x, oscofo_perform64, 0, NULL);
}


// this is the 64-bit perform method audio vectors
void oscofo_perform64(t_oscofo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	// create a simple oscillator
	double *out = outs[0];
	double offset = x->offset;
	double phase = 0.0;
	double phase_incr = 0.1;
	for (long i = 0; i < sampleframes; i++) {
		*out++ = sin(phase) * 0.5 + 0.5;
		phase += phase_incr;
		if (phase > 2 * 3.14159) {
			phase -= 2 * 3.14159;
		}
	}

}
#include "follower.hpp"

#include <limits.h>
#include <math.h>

// ╭─────────────────────────────────────╮
// │              MIR Utils              │
// ╰─────────────────────────────────────╯
//  ─────────────────────────────────────
float FollowerMIR::Mtof(float note, float tunning) {
    return tunning * pow(2.0, (note - 69) / 12.0);
}

// ─────────────────────────────────────
float FollowerMIR::Ftom(float freq, float tunning) {
    return 69 + 12 * log2(freq / tunning);
}

// ─────────────────────────────────────
float FollowerMIR::Freq2Bin(t_float freq, t_float n, t_float sr) {
    t_float bin;
    bin = freq * n / sr;
    return round(bin);
}

// ─────────────────────────────────────
unsigned FollowerMIR::GetPitchBinRanges(std::vector<float> binRanges, t_float thisPitch,
                                        t_float loFreq, t_float hiFreq, t_float pitchTolerance,
                                        int n, t_float sr) {
    int i;
    unsigned cardinality = 0;
    for (i = 0; i < 64; i++)
        binRanges[i] = ULONG_MAX;
    while (mtof(thisPitch) < loFreq)
        thisPitch += 12.0;
    i = 0;
    while (mtof(thisPitch) < hiFreq) {
        binRanges[i] = Freq2Bin(mtof(thisPitch - pitchTolerance), n, sr);
        binRanges[i + 1] = Freq2Bin(mtof(thisPitch + pitchTolerance), n, sr);
        cardinality++;
        thisPitch += 12.0;
        i += 2;
    }
    return (cardinality);
}

// ╭─────────────────────────────────────╮
// │         FollowerScore Utils         │
// ╰─────────────────────────────────────╯
int FollowerScore::Name2Midi(std::string note) {
    char noteName = note[0];
    int classNote = -1;
    switch (noteName) {
    case 'C':
        classNote = 0;
        break;
    case 'D':
        classNote = 2;
        break;
    case 'E':
        classNote = 4;
        break;
    case 'F':
        classNote = 5;
        break;
    case 'G':
        classNote = 7;
        break;
    case 'A':
        classNote = 9;
        break;
    case 'B':
        classNote = 11;
        break;
    default:
        pd_error(NULL, "Invalid note name for %s", note.c_str());
        break;
        return -1;
    }

    if (note[1] == '#' || note[1] == 'b') {
        noteName = note[1];
        if (noteName == '#') {
            classNote++;
        } else {
            classNote--;
        }
        if (std::isdigit(note[2])) {
            int octave = std::stoi(note.substr(2));
            int midi = classNote + 12 + (12 * octave);
            return midi;
        } else {
            pd_error(NULL, "Invalid note name for %s", note.c_str());
            return -1;
        }
    } else {
        if (std::isdigit(note[1])) {
            int octave = std::stoi(note.substr(1));
            int midi = classNote + 12 + (12 * octave);
        } else {
            pd_error(NULL, "Invalid note name for %s", note.c_str());
            return -1;
        }
    }
    return -1;
}

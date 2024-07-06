#include "o.scofo~.hpp"

#include <math.h>

// ╭─────────────────────────────────────╮
// │              MIR Utils              │
// ╰─────────────────────────────────────╯
//  ─────────────────────────────────────
double OScofoMIR::Mtof(double note, double tunning) {
    return tunning * pow(2.0, (note - 69) / 12.0);
}

// ─────────────────────────────────────
double OScofoMIR::Ftom(double freq, double tunning) {
    return 69 + 12 * log2(freq / tunning);
}

// ─────────────────────────────────────
double OScofoMIR::Freq2Bin(double freq, double n, double sr) {
    double bin;
    bin = freq * n / sr;
    return round(bin);
}

// ╭─────────────────────────────────────╮
// │         OScofoScore Utils         │
// ╰─────────────────────────────────────╯
int OScofoScore::Name2Midi(std::string note) {
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

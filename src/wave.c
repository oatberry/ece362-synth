#include "wave.h"

void gen_wavetable() {
    for (int x = 0; x < SAMPLES; x++) {
        // wavetable[x] = 32767 * (sin(2 * M_PI * x / SAMPLES) // sounds kinda like an organ
        //                         + sin(2 * 2 * M_PI * x / SAMPLES) / 8
        //                         + sin(6 * 2 * M_PI * x / SAMPLES) / 16);
		wavetable[x] = 32767 * sin(2 * M_PI * x / SAMPLES);
    }
} 

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

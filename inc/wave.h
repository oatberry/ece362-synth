#ifndef WAVE_H
#define WAVE_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#include <math.h>
#include <stdint.h>

#define SAMPLES 1000

int16_t wavetable[SAMPLES];

void gen_wavetable ();

#endif

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

#ifndef SYNTH_H
#define SYNTH_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#include <stdint.h>
#include <stdlib.h>

void setup_dac ();
void init_tim2 ();

//                       A  Bb B  C  C# D  Eb E  F  F# G  Ab A  Bb B  C  C# D  Eb E  F  F# G  Ab
static uint8_t pressed [24] = { 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0};
// uint8_t pressed [24] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static uint32_t offset [24] = { 0 };

static uint32_t step[24] = {
    1.59 * 4.40000 * (1 << 16) / 2,
    1.59 * 4.66164 * (1 << 16) / 2,
    1.59 * 4.93883 * (1 << 16) / 2,
    1.59 * 5.23251 * (1 << 16) / 2,
    1.59 * 5.54365 * (1 << 16) / 2,
    1.59 * 5.87329 * (1 << 16) / 2,
    1.59 * 6.22254 * (1 << 16) / 2,
    1.59 * 6.59255 * (1 << 16) / 2,
    1.59 * 6.98456 * (1 << 16) / 2,
    1.59 * 7.39989 * (1 << 16) / 2,
    1.59 * 7.83991 * (1 << 16) / 2,
    1.59 * 8.30609 * (1 << 16) / 2,
    1.59 * 8.80000 * (1 << 16) / 2,
    1.59 * 9.32327 * (1 << 16) / 2,
    1.59 * 9.87767 * (1 << 16) / 2,
    1.59 * 10.4650 * (1 << 16) / 2,
    1.59 * 11.0873 * (1 << 16) / 2,
    1.59 * 11.7466 * (1 << 16) / 2,
    1.59 * 12.4451 * (1 << 16) / 2,
    1.59 * 13.1851 * (1 << 16) / 2,
    1.59 * 13.9691 * (1 << 16) / 2,
    1.59 * 14.7998 * (1 << 16) / 2,
    1.59 * 15.6798 * (1 << 16) / 2,
    1.59 * 16.6122 * (1 << 16) / 2
};

#endif

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

#ifndef INPUT_H
#define INPUT_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

//                              A  Bb B  C  C# D  Eb E  F  F# G  Ab A  Bb B  C  C# D  Eb E  F  F# G  Ab
// uint8_t pressed [24] = { 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0};
volatile static uint8_t pressed [24] = { 0 };
// static uint8_t pressed [24] = { 0 };


void setup_adc ();
int read_adc_channel (unsigned int channel);
void setup_buttons ();

#endif

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

#ifndef INPUT_H
#define INPUT_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

void setup_adc ();
int read_adc_channel (unsigned int channel);

#endif

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

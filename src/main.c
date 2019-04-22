#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#include "wave.h"
#include "synth.h"
#include "input.h"

int main(void) {
    gen_wavetable();

    setup_adc();
    setup_dac();
    init_tim2();

    while ( 1 ) asm("wfi");
}

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

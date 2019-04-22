#include "synth.h"
#include "input.h"
#include "wave.h"

void setup_dac() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER4;

    RCC->APB1ENR |= RCC_APB1ENR_DACEN;
    DAC->CR |= DAC_CR_TEN1;
    DAC->CR |= DAC_CR_TSEL1; // Select software trigger
    DAC->CR |= DAC_CR_EN1;
}

void init_tim2() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 48 - 1;
    TIM2->ARR = 10 - 1;

    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    NVIC->ISER[0] = 1 << TIM2_IRQn;
}

void TIM2_IRQHandler() {
    TIM2->SR &= ~TIM_SR_UIF;
    DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1; // Trigger here to avoid delays

    int pitch_bend = read_adc_channel(5);
    int volume = read_adc_channel(6);

    int sample = 0;
    for ( size_t i = 0; i < 24; i++ ) {
        if ( pressed[i] ) {
            offset[i] += step[i] + step[i] * pitch_bend / 1024;
            if ( offset[i] >= SAMPLES << 16 ) {
                offset[i] -= SAMPLES << 16;
            }
            sample += wavetable[offset[i] >> 16];
        }
    }

    sample = volume * (sample / 128) / 4095 + 2048;

    // Handle clipping
    if (sample > 4095) {
        sample = 4095;
    } else if (sample < 0) {
        sample = 0;
    }

    // Output to DAC
    //while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);
    DAC->DHR12R1 = (uint16_t)(sample);
}

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

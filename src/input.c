#include "input.h"

void setup_adc() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER5 | GPIO_MODER_MODER6;

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;     // enable clock to ADC
    RCC->CR2 |= RCC_CR2_HSI14ON;            // turn on hi-spd internal 14MHz clk
    while (!(RCC->CR2 & RCC_CR2_HSI14RDY)); // wait for clock to be ready
    ADC1->CR |= ADC_CR_ADEN;                // enable ADC
    while (!(ADC1->ISR & ADC_ISR_ADRDY));   // wait for ADC to by ready
    while ((ADC1->CR & ADC_CR_ADSTART));    // wait for ADCstart to be 0
}

int read_adc_channel(unsigned int channel) {
    ADC1->CHSELR = 0;                       // unselect all ADC channels
    ADC1->CHSELR |= 1 << channel;           // select the channel

    while (!(ADC1->ISR & ADC_ISR_ADRDY));   // wait for ADC ready
    ADC1->CR |= ADC_CR_ADSTART;             // start the ADC

    while (!(ADC1->ISR & ADC_ISR_EOC));     // wait for end of conversion
    return ADC1->DR;
}

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

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

void init_gpio_ports(void){
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;

    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0 |
            GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0 |
            GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0 |
            GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR7_0 | GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0;

    GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER8 | GPIO_MODER_MODER7 | GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
    GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    GPIOC->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
}

void init_tim6(void){
    NVIC_SetPriority(TIM6_DAC_IRQn, 22);

    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->CR1 &= ~TIM_CR1_CEN;
    TIM6->PSC = 47999;
    TIM6->ARR = 9;
    TIM6->DIER |= TIM_DIER_UIE;
    TIM6->CR1 |= TIM_CR1_CEN;
    NVIC->ISER[0] |= 1 << TIM6_DAC_IRQn;
}

void setup_buttons () {
    init_gpio_ports();
    init_tim6();
}

void TIM6_DAC_IRQHandler(void){
   for(int i = 0; i < 11; i+=1){
       if(!(GPIOC->IDR & (1 << i))){
           if((i != 8) && (i != 9) && (i != 10)){  // the way the IDR and loop was originally set up, the pin corresponding to 8 is invalid
              pressed[i] = 1; // we can't have that piece of the loop messing with the buttons.
           }
       }
       else{
           if((i != 8) && (i != 9) && (i != 10)){
              pressed[i] = 0;
           }
       }
       if(!(GPIOA->IDR & (1 << i))){
           if((i != 4) && (i != 5) && (i != 6) && (i != 8) && (i != 9) && (i != 10)){ // this is SPECIFICALLY so the Handler does not mess with PA4 (the DAC output)
              pressed[i+8] = 1;      // since it is only a check it should not change anything.
           }
           if(i == 8){               // what occurs with the button that originally corresponds to PA4, PA5, and PA6 gets reassigned
               pressed[12] = 1;      // to PA8, PA9, and PA10.
           }
           if(i == 9){
               pressed[13] = 1;
           }
           if(i == 10){
               pressed[14] = 1;
           }
       }
       else{
           if(((i != 4) && (i != 5) && (i != 6) && (i != 8) && (i != 9) && (i != 10))){ // and such, correspondingly the correct button must be turned off as well
               pressed[i+8] = 0;
           }
           if(i == 8){
               pressed[12] = 0;
           }
           if(i == 9){
               pressed[13] = 0;
           }
           if(i == 10){
              pressed[14] = 0;
           }
       }
       if(!(GPIOB->IDR & (1 << i))){
           if((i != 8) && (i != 9) && (i != 10)){ // the way the IDR and loop was originally set up, the pin corresponding to 8 is invalid
              pressed[i+16] = 1; // we can't have that piece of the loop messing with the buttons.
           }
       }
       else{
           if((i != 8) && (i != 9) && (i != 10)){
               pressed[i+16] = 0;
           }
       }
   }

   if(TIM6->SR & TIM_SR_UIF){
       TIM6->SR &= ~TIM_SR_UIF;
   }
}

// vim: set ts=4 sw=4 et fdm=marker fenc=utf-8:

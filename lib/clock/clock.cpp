#include <time.h>
#include <clock.h>
#include "ch32v003fun.h"
constexpr uint32_t PRESCALER = (24000000 / (256 * 50)) - 1;

namespace MatClock
{
    void init()
    {
        // Enable the timer
        RCC->APB2PCENR |= RCC_APB2Periph_TIM1;

        // Reset TIM1 to init all regs
	    RCC->APB2PRSTR |= RCC_APB2Periph_TIM1;
	    RCC->APB2PRSTR &= ~RCC_APB2Periph_TIM1;

        // Prescaler
        TIM1->PSC = PRESCALER;

        // Reload TIM1 to 255 every time we hit 0
        TIM1->ATRLR = 255;

        //Fire interrupt on every reload
        TIM1->RPTCR = 1;

	    // Reload immediately
	    TIM1->SWEVGR |= TIM_UG;

        //enable interrupt on reload
        TIM1->INTFR |= TIM_UIF;

        TIM1->DMAINTENR |= TIM_UIE;
        
        //Enable IRQ lines
        NVIC_EnableIRQ(TIM1_UP_IRQn);

        //Enable/start timer
        TIM1->CTLR1 |= TIM_CEN;
    }
}

extern "C" void TIM1_UP_IRQHandler(void){
    //Increment our current time.
    MatTime::CurrentTime++;
    
    //reset the update interrupt flag
    TIM1->INTFR &= ~TIM_UIF;
}
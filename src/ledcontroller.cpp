#include "ledcontroller.h"
#include "ch32v003fun.h"

namespace MatLed
{
    void init()
    {
        funGpioInitA();
        // initialize digital pin RED_PIN as a push-pull output
        funPinMode(RED_PIN, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP_AF);

        funDigitalWrite(RED_PIN, FUN_HIGH);

        //enable channel 2N capture compare output, positive polarity
        TIM1->CCER |= TIM_CC2NE | TIM_CC2NP;

    	//Channel 1 and 2 are configured in register 1
        // CH2 Mode is output, PWM1 (CC1S = 00, OC1M = 110)
        TIM1->CHCTLR1 |= TIM_OC2M_2 | TIM_OC2M_1 | TIM_OC2M_0;

    	// Set the Capture Compare Register value to 50% initially
    	TIM1->CH2CVR = 128;

        // Enable TIM1 outputs
	    TIM1->BDTR |= TIM_MOE;
    }

    void setColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        TIM1->CH2CVR = red;
    }
}
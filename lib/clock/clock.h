#pragma once
#include <stdint.h>
namespace MatClock
{
    void init();
} // namespace MatTime

extern "C" void TIM1_UP_IRQHandler(void) __attribute__((interrupt));

extern "C" void TIM1_TRG_COM_IRQHandler(void) __attribute__((interrupt));



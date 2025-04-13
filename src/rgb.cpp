#include "ch32v003fun.h"
#include "rgb.h"

// Macros for very short delays.
#define NOP() __asm__ volatile("nop")

#define DELAY_CYCLES_14() \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP();                \
    NOP()

#define DELAY_CYCLES_38() \
    DELAY_CYCLES_14();    \
    DELAY_CYCLES_14();    \

namespace MatRgb
{
     static inline void sendBit(bool bitValue)
    {
        if (bitValue)
        {
            funDigitalWrite(WS2812_PIN, 1)
                DELAY_CYCLES_38(); // T₁H
            funDigitalWrite(WS2812_PIN, 0)
                DELAY_CYCLES_38(); // T₁L
        }
        else
        {   
            funDigitalWrite(WS2812_PIN, 1)
                DELAY_CYCLES_14(); // T₀H
            funDigitalWrite(WS2812_PIN, 0)
                DELAY_CYCLES_38(); // T₀L
        }
    }

    void init()
    {
        //funGpioInitA();
        // initialize digital pin as a push-pull output
        funPinMode(WS2812_PIN, FUN_OUTPUT);
    }

    void draw()
    {
        __disable_irq(); // disable interrupts

        for (int i = 0; i < 18; ++i)
        {
            unsigned char byte = FrameBuffer[i];
            for (int b = 7; b >= 0; --b)
            {
                bool bitVal = (byte >> b) & 0x01;
                sendBit(bitVal);
            }
        }

        __enable_irq(); // re-enable interrupts

        // Send reset: hold line LOW for 50+ µs
        funDigitalWrite(WS2812_PIN, 0);
        //Delay_Us(50);
    }

    void rotate()
    {
        // Rotate the frame buffer by one position.
        unsigned char r = FrameBuffer[0];
        unsigned char g = FrameBuffer[1];
        unsigned char b = FrameBuffer[2];
        for (int i = 0; i < 17; i+=3)
        {
            FrameBuffer[i] = FrameBuffer[i + 3];
            FrameBuffer[i+1] = FrameBuffer[i + 4];
            FrameBuffer[i+2] = FrameBuffer[i + 5];
        }

        FrameBuffer[15] = r;
        FrameBuffer[16] = g;
        FrameBuffer[17] = b;
    }

    void clear(){
        for (int i = 0; i < 18; ++i)
        {
            FrameBuffer[i] = 0;
        }
    }
}
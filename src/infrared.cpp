#include "ch32v003fun.h"
#include "infrared.h"
#include "stdint.h"
namespace MatInfrared
{

    // Transmist a single character, bit at a time, with 1 start bit, and 1 stop bit
    void transmitChar(uint8_t c)
    {
        // transmit the start bit
        transmitZero();
        // transmit all 8 data bits.
        // 8
        if (c & 0b00000001)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }
        // 7
        if (c & 0b00000010)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }
        // 6
        if (c & 0b00000100)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }
        // 5
        if (c & 0b00001000)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }
        // 4
        if (c & 0b00010000)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }
        // 3
        if (c & 0b00100000)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }
        // 2
        if (c & 0b01000000)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }
        // 1
        if (c & 0b10000000)
        {
            transmitOne();
        }
        else
        {
            transmitZero();
        }

        // transmit stop bit
        transmitOne();
    }

    void transmitOne()
    {
        Delay_Us(PULSE_WIDTH * 2 * 34);
    }
    

    // Cycle pin 32 times at 38khz to send a zero
    void transmitZero()
    {
        // 1
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 2
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 3
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 4
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 5
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 6
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 7
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 8
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 9
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 10
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 11
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 12
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 13
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 14
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 15
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 16
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 17
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 18
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 19
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 20
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 21
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 22
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 23
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 24
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 25
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 26
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 27
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 28
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 29
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 30
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        // 31
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);

        //Fine tuned to 1200bps
        /*
        // 32
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_HIGH);
        Delay_Us(PULSE_WIDTH);
        funDigitalWrite(TX_PIN, FUN_LOW);
        */
    }
}
#pragma once
#define TX_PIN PC1
#define PULSE_WIDTH 12
namespace MatInfrared
{
    void transmitChar(uint8_t c);
    void transmitOne();
    void transmitZero();
    void transmitStop();
}
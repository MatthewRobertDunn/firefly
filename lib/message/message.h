#pragma once
#include <stdint.h>
namespace MatMessage
{
    #define MAX_MESSAGE_TYPE 0
    #define MAX_MESSAGE_LENGTH 8
    #define MESSAGE_TIMEOUT 5 // timeout after 5*20ms

    enum class MessageType : uint8_t
    {
        Time = 0,
    };

    struct MessageHeader
    {
        MessageType type;
        uint8_t length;
        uint16_t checksum;
    };


    inline void (*onMessageReceived)(MessageHeader &msg, uint8_t* data) = 0;
    inline void (*sendCharacter)(uint8_t data) = 0;
    void send(MessageHeader &msg, uint8_t* data);
    void checkForMessages(uint8_t data);
}

#pragma once
#include <stdint.h>
#include <vector>
namespace MatMessage
{
    #define MAX_MESSAGE_TYPE 0
    #define MAX_MESSAGE_LENGTH 8
    #define MESSAGE_TIMEOUT 5 // timeout after 5*20ms

    enum class MessageType : uint8_t
    {
        Time = 0,
    };

    struct Message
    {
        MessageType type;
        uint8_t length;
        uint16_t checksum;
        uint8_t* data;
    };

    inline void (*onMessageReceived)(Message &msg) = 0;
    void send(Message &msg);
    void checkForMessages();
}

#include "message.h"
#include <time.h>
namespace MatMessage
{
    enum class ReceiveState : uint8_t
    {
        Type = 1,
        Length = 2,
        Checksum = 3,
        Data = 4,
    };

    ReceiveState currentReceiveState = ReceiveState::Type;
    MessageHeader currentMessage = {MessageType::Time, 0, 0};
    uint8_t currentMessageData[MAX_MESSAGE_LENGTH];
    uint8_t bytesReceived = 0;
    uint32_t lastRecievedTime = 0;

    void send(MessageHeader &msg, uint8_t* data)
    {
        // send the type
        sendCharacter(static_cast<uint8_t>(msg.type));

        // send the length
        sendCharacter(msg.length);

        // send the checksum
        sendCharacter(msg.checksum >> 8);
        sendCharacter(msg.checksum & 0xFF);

        // send the data
        for (uint8_t i = 0; i < msg.length; i++)
        {
            sendCharacter(data[i]);
        }
    }

    /**
     *    Checks for incoming messages and updates the current receive state accordingly.
     *
     *    This function is responsible for handling the receipt of messages, including
     *    checking the message type, length, checksum, and data. It updates the current
     *    receive state based on the received data and calls the onMessageReceived callback
     *    when a complete message is received.
     *
     *    @return None
     */
    void checkForMessages(uint8_t data)
    {
        if (MatTime::CurrentTime - lastRecievedTime > MESSAGE_TIMEOUT)
        {
            currentReceiveState = ReceiveState::Type;
            bytesReceived = 0;
        }

        lastRecievedTime = MatTime::CurrentTime;

        switch (currentReceiveState)
        {
        case ReceiveState::Type:
            if (data > MAX_MESSAGE_TYPE)
            {
                return; // Invalid message type, keep waiting
            }
            currentMessage.type = static_cast<MessageType>(data);
            currentReceiveState = ReceiveState::Length;
            break;

        case ReceiveState::Length:
            if (data > MAX_MESSAGE_LENGTH)
            {
                // invalid message length, packet is invalid
                currentReceiveState = ReceiveState::Type;
                return;
            }
            currentMessage.length = data;
            currentReceiveState = ReceiveState::Checksum;
            break;

        case ReceiveState::Checksum:
            if (bytesReceived == 0)
            {
                currentMessage.checksum = data << 8;
                bytesReceived++;
                return;
            }
            else if (bytesReceived == 1)
            {
                currentMessage.checksum |= data;
                currentReceiveState = ReceiveState::Data;
                bytesReceived = 0;
            }
            break;

        case ReceiveState::Data:
            currentMessageData[bytesReceived] = data;
            bytesReceived++;
            if (bytesReceived == currentMessage.length)
            {
                if (onMessageReceived != 0)
                {
                    onMessageReceived(currentMessage, currentMessageData);
                }
                currentReceiveState = ReceiveState::Type;
            }
            break;
        }
    }
}
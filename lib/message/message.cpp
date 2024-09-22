#include "message.h"
#include <time.h>
#include <crc16.h>
namespace MatMessage
{
    enum class ReceiveState : uint8_t
    {
        Type = 1,
        Length = 2,
        Data = 3,
        Checksum = 4,
    };

    ReceiveState currentReceiveState = ReceiveState::Type;
    MessageHeader currentMessage = {MessageType::Time, 0, 0};
    uint8_t currentMessageData[MAX_MESSAGE_LENGTH];
    uint8_t bytesReceived = 0;
    uint32_t lastRecievedTime = 0;

    void send(MessageHeader &msg, uint8_t *data)
    {
        // send the type
        auto byte = static_cast<uint8_t>(msg.type);
        sendCharacter(byte);
        uint16_t crc = MatCrc::crc16initial(byte);

        // send the length
        sendCharacter(msg.length);
        crc = MatCrc::crc16update(msg.length, crc);

        // send the data
        for (uint8_t i = 0; i < msg.length; i++)
        {
            sendCharacter(data[i]);
            crc = MatCrc::crc16update(data[i], crc);
        }
        // send the checksum
        sendCharacter(crc >> 8);
        sendCharacter(crc & 0xFF);
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
            currentMessage.calculatedChecksum = MatCrc::crc16initial(data);
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
            currentMessage.calculatedChecksum = MatCrc::crc16update(data, currentMessage.calculatedChecksum);
            currentReceiveState = ReceiveState::Data;
            break;

        case ReceiveState::Data:
            currentMessageData[bytesReceived] = data;
            currentMessage.calculatedChecksum = MatCrc::crc16update(data, currentMessage.calculatedChecksum);
            bytesReceived++;
            if (bytesReceived == currentMessage.length)
            {
                bytesReceived = 0;
                currentReceiveState = ReceiveState::Checksum;
            }
            break;
        case ReceiveState::Checksum:
            if (bytesReceived == 0)
            {
                currentMessage.receivedChecksum = data << 8;
                bytesReceived++;
                return;
            }
            else if (bytesReceived == 1)
            {
                currentMessage.receivedChecksum |= data;
                currentReceiveState = ReceiveState::Type;
                bytesReceived = 0;

                if(currentMessage.receivedChecksum == currentMessage.calculatedChecksum)
                {
                    onMessageReceived(currentMessage, currentMessageData);
                }
            }
            break;
        }
    }
}
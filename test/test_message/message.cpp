#include <message.h>
#include <unity.h>
#include <crc16.h>
void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

uint8_t *messageData = 0;
MatMessage::MessageHeader messageHeader = {MatMessage::MessageType::Time, 0, 0};

void onMessageReceived(MatMessage::MessageHeader &msg, uint8_t *data)
{
    messageHeader.type = msg.type;
    messageHeader.length = msg.length;
    messageHeader.receivedChecksum = msg.receivedChecksum;
    messageData = data;
}

void test_message()
{
    MatMessage::onMessageReceived = onMessageReceived;
    
    // Send message type
    auto byte = static_cast<uint8_t>(MatMessage::MessageType::Time);
    MatMessage::checkForMessages(byte);
    auto crc = MatCrc::crc16initial(byte);

    // Send message length
    MatMessage::checkForMessages(static_cast<uint8_t>(4));
    crc = MatCrc::crc16update(4, crc);
   
    // send message data
    MatMessage::checkForMessages(static_cast<uint8_t>(0x00));
    crc = MatCrc::crc16update(0x00, crc);
    MatMessage::checkForMessages(static_cast<uint8_t>(0x01));
    crc = MatCrc::crc16update(0x01, crc);
    MatMessage::checkForMessages(static_cast<uint8_t>(0x02));
    crc = MatCrc::crc16update(0x02, crc);
    MatMessage::checkForMessages(static_cast<uint8_t>(0x03));
    crc = MatCrc::crc16update(0x03, crc);

    // send message checksum
    MatMessage::checkForMessages(crc >> 8);
    MatMessage::checkForMessages(crc & 0xFF);

    TEST_ASSERT_EQUAL(MatMessage::MessageType::Time, messageHeader.type);
    TEST_ASSERT_EQUAL(4, messageHeader.length);
    TEST_ASSERT_EQUAL(31457, messageHeader.receivedChecksum);
    TEST_ASSERT_EQUAL(0, messageData[0]);
    TEST_ASSERT_EQUAL(1, messageData[1]);
    TEST_ASSERT_EQUAL(2, messageData[2]);
    TEST_ASSERT_EQUAL(3, messageData[3]);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_message);
    UNITY_END();
}

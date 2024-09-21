#include <message.h>
#include <unity.h>

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
    messageHeader.checksum = msg.checksum;
    messageData = data;
}

void test_message()
{
    MatMessage::onMessageReceived = onMessageReceived;
    // Send message type
    MatMessage::checkForMessages(static_cast<uint8_t>(MatMessage::MessageType::Time));

    // Send message length
    MatMessage::checkForMessages(static_cast<uint8_t>(4));

    // send message checksum
    MatMessage::checkForMessages(static_cast<uint8_t>(0xAA));
    MatMessage::checkForMessages(static_cast<uint8_t>(0xFF));
    
    // send message data
    MatMessage::checkForMessages(static_cast<uint8_t>(0x00));
    MatMessage::checkForMessages(static_cast<uint8_t>(0x01));
    MatMessage::checkForMessages(static_cast<uint8_t>(0x02));
    MatMessage::checkForMessages(static_cast<uint8_t>(0x03));

    TEST_ASSERT_EQUAL(MatMessage::MessageType::Time, messageHeader.type);
    TEST_ASSERT_EQUAL(4, messageHeader.length);
    TEST_ASSERT_EQUAL(0xAAFF, messageHeader.checksum);
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

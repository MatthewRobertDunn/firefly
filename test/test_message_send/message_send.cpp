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
    MatMessage::sendCharacter = MatMessage::checkForMessages;

    MatMessage::MessageHeader msg = {MatMessage::MessageType::Time, 4, 0};
    uint8_t data[] = {0, 1, 2, 3};
    MatMessage::send(msg, data);


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

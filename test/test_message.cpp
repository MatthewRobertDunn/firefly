#include <message.h>
#include <unity.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


void onMessageReceived(MatMessage::MessageHeader &msg, uint8_t* data) {
    TEST_ASSERT_EQUAL(0, msg.type);
    TEST_ASSERT_EQUAL(4, msg.length);
    TEST_ASSERT_EQUAL(0xAAFF, msg.checksum);
    TEST_ASSERT_EQUAL(1, data[0]);
    TEST_ASSERT_EQUAL(2, data[1]);
    TEST_ASSERT_EQUAL(3, data[2]);
    TEST_ASSERT_EQUAL(4, data[3]);
}

int main( int argc, char **argv) {
  MatMessage::onMessageReceived = onMessageReceived;
  
  
  //Send message type
  MatMessage::checkForMessages(static_cast<uint8_t>(MatMessage::MessageType::Time));

  //Send message length
  MatMessage::checkForMessages(static_cast<uint8_t>(4));

  //send message checksum
  MatMessage::checkForMessages(static_cast<uint8_t>(0xAA));
  MatMessage::checkForMessages(static_cast<uint8_t>(0xFF));

  //send message data
  MatMessage::checkForMessages(static_cast<uint8_t>(0x00));
  MatMessage::checkForMessages(static_cast<uint8_t>(0x01));
  MatMessage::checkForMessages(static_cast<uint8_t>(0x02));
  MatMessage::checkForMessages(static_cast<uint8_t>(0x03));
}

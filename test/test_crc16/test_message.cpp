#include <crc16.h>
#include <unity.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

//Ensure CRC matches modbus specs
void test_crc16()
{
    auto crc = MatCrc::crc16initial('1');
    crc = MatCrc::crc16update('2', crc);
    crc = MatCrc::crc16update('3', crc);
    crc = MatCrc::crc16update('4', crc);
    crc = MatCrc::crc16update('5', crc);
    crc = MatCrc::crc16update('6', crc);
    crc = MatCrc::crc16update('7', crc);
    crc = MatCrc::crc16update('8', crc);
    crc = MatCrc::crc16update('9', crc);

    TEST_ASSERT_EQUAL(0x4B37, crc);
}

void test_crc16_hello()
{
    auto crc = MatCrc::crc16initial('h');
    crc = MatCrc::crc16update('e', crc);
    crc = MatCrc::crc16update('l', crc);
    crc = MatCrc::crc16update('l', crc);
    crc = MatCrc::crc16update('o', crc);
    TEST_ASSERT_EQUAL(0x34F6, crc);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_crc16);
    RUN_TEST(test_crc16_hello);
    UNITY_END();
}

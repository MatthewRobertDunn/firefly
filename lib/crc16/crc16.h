#include <stdint.h>
namespace MatCrc
{
    uint16_t crc16initial(const uint8_t data);

    uint16_t crc16update(const uint8_t data, const uint16_t crc);

}
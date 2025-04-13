#include "ch32v003fun.h"
#include "infrared.h"
#include "usart.h"
#include <time.h>
#include <clock.h>
#include <message.h>
#include <crc16.h>
#include "rgb.h"
#include "ch32v003fun.h"
void loop();

// the setup function runs once when you press reset or power the board
int main()
{
   SystemInit();
  //MatClock::init();
  //UART_init();
  funGpioInitAll(); 
  MatRgb::init();
  //MatRgb::FrameBuffer[0] = 0xFF;
  //MatRgb::FrameBuffer[17] = 0xFF;

  while (true)
  {
    MatRgb::draw();
    MatRgb::rotate();
    Delay_Ms(100);
  }
}


/**
 *  auto startTime = MatTime::CurrentTime;
    loop();
    // Spin until we've used up all the time

    while (startTime == MatTime::CurrentTime)
    {
      Delay_Us(100);
    }
 */

// the loop function runs over and over again forever
void loop()
{
  // MatLed::setColor(MatTime::CurrentTime % 255, 0, 0);

  // MatMessage::MessageHeader msg;
  // uint8_t data[4] =
  //     {(uint8_t)(MatTime::CurrentTime & 0xFF000000 >> 24),
  //      (uint8_t)(MatTime::CurrentTime & 0x00FF0000 >> 16),
  //      (uint8_t)(MatTime::CurrentTime & 0x0000FF00 >> 8),
  //      (uint8_t)(MatTime::CurrentTime & 0x000000FF)};
  
  // msg.type = MatMessage::MessageType::Time;
  // msg.length = 4;
  // msg.receivedChecksum = 0;
  // MatMessage::send(msg,&data[0]);

  // auto crc = MatCrc::crc16initial(0xff);
  // crc = MatCrc::crc16update(0xAA, crc);

  // MatMessage::send(msg, (uint8_t*)&crc);

  // //MatMessage::checkForMessages();
}

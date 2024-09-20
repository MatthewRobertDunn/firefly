#include "ch32v003fun.h"
#include "infrared.h"
#include "ledcontroller.h"
#include "usart.h"
#include <time.h>
#include <clock.h>
#include <message.h>
void loop();

// the setup function runs once when you press reset or power the board
int main()
{
  SystemInit();
  MatClock::init();
  UART_init();
  MatLed::init();

  while (true)
  {
    auto startTime = MatTime::CurrentTime;
    loop();
    // Spin until we've used up all the time

    while (startTime == MatTime::CurrentTime)
    {
      Delay_Us(100);
    }
  }
}

// the loop function runs over and over again forever
void loop()
{
  MatLed::setColor(MatTime::CurrentTime % 255, 0, 0);

  MatMessage::MessageHeader msg;
  uint8_t data[4] =
      {(uint8_t)(MatTime::CurrentTime & 0xFF000000 >> 24),
       (uint8_t)(MatTime::CurrentTime & 0x00FF0000 >> 16),
       (uint8_t)(MatTime::CurrentTime & 0x0000FF00 >> 8),
       (uint8_t)(MatTime::CurrentTime & 0x000000FF)};
  
  msg.type = MatMessage::MessageType::Time;
  msg.length = 4;
  msg.checksum = 0;
  MatMessage::send(msg,&data[0]);

  //MatMessage::checkForMessages();
}

#include "ch32v003fun.h"
#include "infrared.h"
#include "ledcontroller.h"
#include "usart.h"
#include "time.h"
void loop();

// the setup function runs once when you press reset or power the board
int main()
{
  SystemInit();
  MatTime::init();
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
  /*MatInfrared::transmitChar('H');
  MatInfrared::transmitChar('e');
  MatInfrared::transmitChar('l');
  MatInfrared::transmitChar('l');
  MatInfrared::transmitChar('o');
  MatInfrared::transmitChar(' ');
  MatInfrared::transmitChar('W');
  MatInfrared::transmitChar('o');
  MatInfrared::transmitChar('r');
  MatInfrared::transmitChar('l');
  MatInfrared::transmitChar('d');
  MatInfrared::transmitChar('!');
  MatInfrared::transmitChar('!');
  */
  MatLed::setColor(MatTime::CurrentTime % 255,0,0); 
}

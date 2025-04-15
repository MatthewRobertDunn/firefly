#include "animations.h"
#include "rgb.h"
#include <time.h>
#define PERIOD 1024;
void clock();
int currentAnimation = 0;

void MatAnimations::init(){
    MatRgb::FrameBuffer[1] = 32;
}

void MatAnimations::tick()
{
    clock();
}


void clock(){
    if(MatTime::CurrentTime % 50 == 0){
        MatRgb::rotate();
    }
}

void idle(){
    auto value = MatTime::CurrentTime % PERIOD;
    if(value > 32)
    {
        value = 0;
    }

    MatRgb::FrameBuffer[0] = value;
    MatRgb::FrameBuffer[1] = value;

    value = (MatTime::CurrentTime + 742) % PERIOD;
    if(value > 32)
    {
        value = 0;
    }
    MatRgb::FrameBuffer[1 * 3] = value;
    MatRgb::FrameBuffer[1 * 3 + 1] = value;


    value = (MatTime::CurrentTime + 350) % PERIOD;
    if(value > 32)
    {
        value = 0;
    }
    MatRgb::FrameBuffer[2 * 3] = value;
    MatRgb::FrameBuffer[2 * 3 + 1] = value;


    value = (MatTime::CurrentTime + 181) % PERIOD;
    if(value > 32)
    {
        value = 0;
    }
    MatRgb::FrameBuffer[3 * 3] = value;
    MatRgb::FrameBuffer[3 * 3 + 1] = value;


    value = (MatTime::CurrentTime + 69) % PERIOD;
    if(value > 32)
    {
        value = 0;
    }
    MatRgb::FrameBuffer[4 * 3] = value;
    MatRgb::FrameBuffer[4 * 3 + 1] = value;


    value = (MatTime::CurrentTime + 241) % PERIOD;
    if(value > 32)
    {
        value = 0;
    }
    MatRgb::FrameBuffer[5 * 3] = value;
    MatRgb::FrameBuffer[5 * 3 + 1] = value;
}
#pragma once
#define WS2812_PIN PA2
namespace MatRgb {
    //inline unsigned char FrameBuffer[18] = {0};
    inline unsigned char FrameBuffer[18] = {0x00};
    void init();
    void draw();
    void rotate();
    void clear();
}
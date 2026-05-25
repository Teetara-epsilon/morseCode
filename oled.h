#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class Oled {
private:
    Adafruit_SSD1306 display;

public:
    Oled();

    void Begin();
    void Clear();

    void PrintChar(char c);
    void PrintMorseSignal(String signal);
};

#endif
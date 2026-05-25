#include "Oled.h"

Oled::Oled()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
}

void Oled::Begin(){
    Wire.begin();

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        while(true){
            // OLEDが見つからない場合はここで止まる
        }
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(0, 0);

    display.display();
}

void Oled::Clear(){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.display();
}

void Oled::PrintChar(char c){
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.print(c);

    display.display();
}

void Oled::PrintMorseSignal(String signal){
    int savedX = display.getCursorX();
    int savedY = display.getCursorY();

    const int morseAreaY = 56;
    const int morseAreaHeight = 8;
    const int charWidth = 6;

    const int labelX = 48;      // "Morse: "の左端
    const int labelWidth = 42;  // "Morse: "７文字*6px

    display.fillRect(labelX, morseAreaY,
        SCREEN_WIDTH - labelX,
        morseAreaHeight,
        SSD1306_BLACK);

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(labelX, morseAreaY);
    display.print("Morse: ");

    int signalWidth = signal.length() * charWidth;
    int signalX = SCREEN_WIDTH - signalWidth;
    if( signalX < labelX + labelWidth){ signalX = labelX + labelWidth; }

    display.setCursor(signalX, morseAreaY);
    display.print(signal);

    display.setCursor(savedX, savedY);
    display.display();
}
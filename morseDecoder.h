#ifndef MORSE_DECODER_H
#define MORSE_DECODER_H

#include "demodulation.h"
#include <string.h>
#include "oled.h"
#include <Arduino.h>

class MorseContext{
    char c;
    String str;

public:
    MorseContext(){
        c = '\0';
        str = "";
    }
    
    MorseContext(char nextChar, String morseSignal){
        c = nextChar;
        str = morseSignal;
    }
    void ShowChar(Oled& oled){
        Serial.print("char: ");
        Serial.print(c);
        oled.PrintChar(c);
    }
    void ShowMorseSignal(Oled& oled){
        Serial.print("  MorseSignal: ");
        Serial.print(str);
        oled.PrintMorseSignal(str);
    }

    bool HasChar(){
        return c != '\0';
    }
};

class MorseDecoder{

    public:
    static MorseContext Decode(MorseElement element);
    static char DecodePattern(const char* pattern);
};

#endif
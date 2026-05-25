#include "digitalLevel.h"
#include <Arduino.h>

const digitalLevel HorL_PULL = LevelHigh;

DigitalLevel::DigitalLevel(digitalLevel value){
    this -> value = value; 
    this -> timer = Timer();
    timer.set();
    timer.start();
}


DigitalLevel DigitalLevel::Create(){ return  DigitalLevel( HorL_PULL); }

bool DigitalLevel::IsInvalidPressTime(unsigned long time){
    if(time < MIN_KEY_DOWN_TIME) return true;
    if(time > MAX_KEY_DOWN_TIME) return true;
    return false;
}

void DigitalLevel::Next(Voltage next_value, Totalling& total){
    if(value == LevelHigh){
        // 現在 LevelHigh なら
        if( next_value.value > FALL_THRESHOLD ){
            edgeDetected = false;
            return;
        }
        Serial.println("Falldwon");
        
        value = LevelLow;
        edgeDetected = true;
        isInvalidKeyDown = false;
        timer.stop();
        timer.set();
        total.time = timer.GetElapsed();
        if( total.time < MIN_EMPTY_TIME)
            isInvalidKeyDown = true;
    }
    else{
        // 現在 LevelLow なら
        if( next_value.value < RAISE_THRESHOLD ){
            edgeDetected = false;
            return;
        }
        Serial.println("Raiseup");
        
        value = LevelHigh;
        edgeDetected = true;
        timer.stop();
        timer.set();
        if(isInvalidKeyDown){
            timer.start();
            return;
        }

        total.time = timer.GetElapsed();
        if( IsInvalidPressTime(total.time) ){
            isInvalidKeyDown = true;
        }
    }
    timer.start();
}
digitalLevel DigitalLevel::GetValue(){ return value; }
unsigned long DigitalLevel::GetTime(){ return timer.GetElapsed(); }
bool DigitalLevel::IsEdged(){ return edgeDetected; }
bool DigitalLevel::IsInvalid(){ return isInvalidKeyDown; }
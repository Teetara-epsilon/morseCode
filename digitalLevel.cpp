#include "digitalLevel.h"
#include <Arduino.h>

extern unsigned long time;
extern int n;

const digitalLevel HorL_PULL = LevelHigh;

DigitalLevel(digitalLevel value){
    this -> value = value; 
    this -> timer = Timer();
    timer.set();
    if(value == LevelLow)
        timer.start();
}

public:
static DigitalLevel Create(){ return  DigitalLevel( HorL_PULL); }

DigitalLevel Next(Voltage next_value, Totalling total){
if(value == LevelHigh){
    // 現在 LevelHigh なら
    if( next_value.value < FALL_THRESHOLD ){
    return  DigitalLevel(LevelLow);
    }
    return  *this;
}
else{
    // 現在 LevelLow なら
    if( next_value.value > RAISE_THRESHOLD ){
    timer.stop();
    total.totaltime += timer.GetElapsed();
    total.n++;

    total.ShowAve();
    return  DigitalLevel(LevelHigh);
    }
    return  *this;
}
}
digitalLevel GetValue(){ return value; }
unsigned long GetTime(){ return timer.GetElapsed(); }
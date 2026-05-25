#ifndef DEMODULATION_H
#define DEMODULATION_H

#include "digitalLevel.h"

enum MorseElement{
    Dit,        // トン ・
    Dah,        // ツー ー
    IntraGap,   // 文字内空白
    LetterGap,  // 文字間空白
    WordGap,    // 単語間空白

    Invalid     // 無効な入力
};

// 誤差許容割合値
const float MIN_UNIT_ERROR_RATE = 0.8;

// V
const MorseElement TEST[] = {
    Dit,
    IntraGap,
    Dit,
    IntraGap,
    Dit,
    IntraGap,
    Dah
};

const int TEST_LENGTH = sizeof(TEST) / sizeof(TEST[0]);

class Demodulation{
    const int DitTime = 1;
    const int DahTime = 3;
    const int WGTime = 7;
    DigitalLevel currentLevel = DigitalLevel::Create();
    Totalling total = Totalling();
    int testProgress = 0;
    unsigned long unitTime = 90;

    unsigned long totalEffectiveTimeForTest = 0;
    int totalUnits = 0;
    
    MorseElement Testing(DigitalLevel signal){
        MorseElement t = TEST[testProgress];
        if( t == Dit || t == IntraGap ){
            totalEffectiveTimeForTest += signal.GetTime();
            totalUnits += DitTime;
        }
        else if( t == Dah || t == LetterGap ){
            totalEffectiveTimeForTest += signal.GetTime();
            totalUnits += DahTime;
        }
        else if( t == WordGap ){
            totalEffectiveTimeForTest += signal.GetTime();
            totalUnits += WGTime;
        }
        testProgress++;
        if( testProgress == TEST_LENGTH ){ 
            unitTime = totalEffectiveTimeForTest / totalUnits;
        }
        return t;
    }

    public:
    MorseElement Demodulate(int analogValue){
        Voltage volt = Voltage(analogValue); 
        currentLevel.Next(volt, total);

        if( currentLevel.IsInvalid() ){ return Invalid; }
        if( !currentLevel.IsEdged() ){ return Invalid; }
        //if( testProgress < TEST_LENGTH ){ return Testing(currentLevel); }

        unsigned long time = currentLevel.GetTime();
        unsigned long minUnit = MIN_UNIT_ERROR_RATE * unitTime;
        if( time < DahTime * minUnit){
            if( currentLevel.GetValue() == LevelLow ){ return IntraGap; }
            else{ return Dit; }
        }
        else if( time < WGTime * minUnit){
            if( currentLevel.GetValue() == LevelLow ){ return LetterGap; }
            else{ return Dah; }
        }
        else{
            if( currentLevel.GetValue() == LevelLow ){ return WordGap; }
        }
        return Invalid;
    }
};
#endif
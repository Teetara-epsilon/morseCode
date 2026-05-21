#ifndef Digital_Level_H
#define Digital_Level_H

#include "timer.h"
#include "voltage.h"


enum digitalLevel{
  LevelLow,
  LevelHigh
};

class DigitalLevel{
  digitalLevel value;
  Timer timer;

  const int RAISE_THRESHOLD = 600;
  const int FALL_THRESHOLD = 400;
  
  DigitalLevel(digitalLevel value){}

  public:
  static DigitalLevel Create(){}
  
  DigitalLevel Next(Voltage next_value){}
  digitalLevel GetValue(){ return value; }
  unsigned long GetTime(){ return timer.GetElapsed(); }
};

#endif
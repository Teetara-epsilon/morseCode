#ifndef DIGITAl_LEVEl_H
#define DIGITAl_LEVEl_H

#include "timer.h"
#include "voltage.h"
#include "totalling.h"


enum digitalLevel{
  LevelLow,
  LevelHigh
};

class DigitalLevel{
  digitalLevel value;
  Timer timer;

  static const int RAISE_THRESHOLD = 600;
  static const int FALL_THRESHOLD = 400;
  
  DigitalLevel(digitalLevel value);

  public:
  static DigitalLevel Create();
  
  DigitalLevel Next(Voltage next_value, Totalling& total);
  digitalLevel GetValue();
  unsigned long GetTime();
};

#endif
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
  bool edgeDetected = false;
  bool isInvalidKeyDown = false;

  static const int RAISE_THRESHOLD = 600;
  static const int FALL_THRESHOLD = 400;
  static const unsigned long MIN_EMPTY_TIME = 70;
  static const unsigned long MAX_KEY_DOWN_TIME = 1000;
  static const unsigned long MIN_KEY_DOWN_TIME = 70;
  
  DigitalLevel(digitalLevel value);
  bool IsInvalidPressTime(unsigned long time);

  public:
  static DigitalLevel Create();
  
  void Next(Voltage next_value, Totalling& total);
  digitalLevel GetValue();
  unsigned long GetTime();
  bool IsEdged();
  bool IsInvalid();
};

#endif
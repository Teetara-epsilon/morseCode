#ifndef VOLTAGE_H
#define VOLTAGE_H

class Voltage{
  public:
  int value;

  const int MIN = 0;
  const int MAX = 1023;
  
  Voltage(int value){
    if(value < MIN) value = MIN;
    if(value > MAX) value = MAX;
    this->value = value;
  }
};

#endif
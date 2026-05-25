#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer{
  bool is_runnning = false;
  unsigned long start_time = 0;
  unsigned long elapsed_time = 0;
  unsigned long previous_time = 0;
  
  public:
  void set(){ 
    previous_time = elapsed_time;
    elapsed_time = 0; 
    is_runnning = 0; 
  }
  
  void start(){ 
    is_runnning = true; 
    start_time =  millis();
  }

  void stop(){ 
    if(is_runnning){
      is_runnning = false;
      elapsed_time += millis() - start_time;
    }
  }

  unsigned long GetElapsed(){ return previous_time; }
  
  bool IsRunnning(){ return is_runnning; }
};

#endif
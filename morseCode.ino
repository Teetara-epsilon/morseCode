#include "timer.h"
#include "voltage.h"
#include "digitalLevel.h"

const int PIN_MORSE = A0;

unsigned long time = 0;
int n = 0;
DigitalLevel currentLevel = DigitalLevel::Create();
void setup() {
  Serial.begin(9600);
}

void loop() {
  
  Voltage volt = Voltage((analogRead( PIN_MORSE ))); 
  DigitalLevel next = currentLevel.Next(volt);

  currentLevel = next;
}

class Chart{
  const int X = 0;
  const int Y = 0;
  const int WIDTH = 50;
  const int HEIGHT = 70;
  int latest_v = 0;

  public:
  void update(int voltage){
    latest_v = voltage;
  }
};


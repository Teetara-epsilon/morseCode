#include "demodulation.h"
#include "morseDecoder.h"
#include "oled.h"

const int PIN_MORSE = A0;

Demodulation demodulation = Demodulation();
Oled oled = Oled();

void setup() {
  Serial.begin(9600);
  oled.Begin();
}

void loop() {
  
  MorseElement signal = demodulation.Demodulate(analogRead( PIN_MORSE )); 
  if( signal == Invalid ){ return; }

  MorseContext ctx = MorseDecoder::Decode(signal);
  if(!ctx.HasChar()){ return; }

  ctx.ShowChar(oled);
  ctx.ShowMorseSignal(oled);
  Serial.println();
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


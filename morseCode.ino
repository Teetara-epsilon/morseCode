
const int PIN_MORSE = A0;
const digitalLevel HorL_PULL = LelelHigh;

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

class Timer{
  bool is_runnning = false;
  unsigned long start_time = 0;
  unsigned long elapsed_time = 0;
  
  public:
  void set(){ 
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
  unsigned long GetElapsed(){ return elapsed_time; }
  bool IsRunnning(){ return is_runnning; }
};
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

enum digitalLevel{
  LelelLow,
  LelelHigh
};
class DigitalLevel{
  digitalLevel value;
  Timer timer;

  const int RAISE_THRESHOLD = 600;
  const int FALL_THRESHOLD = 400;
  
  DigitalLevel(digitalLevel value){
      this -> value = value; 
      this -> timer = Timer();
      timer.set();
      timer.start();
    }

  public:
  static DigitalLevel Create(){ return  DigitalLevel( HorL_PULL); }
  
  DigitalLevel Next(Voltage next_value){
    if(value == LelelHigh){
      // 現在 LelelHigh なら
      if( next_value.value < FALL_THRESHOLD ){
        return  DigitalLevel(LelelLow);
      }
      return  *this;
    }
    else{
      // 現在 LelelLow なら
      if( next_value.value > RAISE_THRESHOLD ){
        timer.stop();
        time += timer.GetElapsed();
        n++;

        Serial.println("average time: ");
        Serial.println(time/n);
        return  DigitalLevel(LelelHigh);
      }
      return  *this;
    }
  }
  digitalLevel GetValue(){ return value; }
  unsigned long GetTime(){ return timer.GetElapsed(); }
};
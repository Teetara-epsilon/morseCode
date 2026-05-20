
const int PIN_MORSE = A0;
const digitalLevel HorL_PULL = High;

DigitalLevel currentLevel;
Timer timer;
void setup() {
  currentLevel = DigitalLevel::Create();

  timer = Timer();
  timer.set();
}

void loop() {
  
  Voltage volt = Voltage((PIN_MORSE)); 
  currentLevel = currentLevel.Next(volt);

  // トン の成立閾値を測定
  if(currentLevel.GetValue() == Low)
    timer.start();
  if(timer.is_runnning){
    if(currentLevel.GetValue() == High)
      timer.stop();
  }
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
  public: bool is_runnning =false;
  unsigned long start_time = 0;
  unsigned long elapsed_time = 0;
  
  public:
  void set(){ elapsed_time = 0; }
  void start(){ 
    is_runnning = true; 
    start_time =  millis();
  }
  void stop(){ 
    is_runnning = false;
    elapsed_time += millis() - start_time;
  }
  unsigned long getCounter(){ return elapsed_time; }
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
  Low,
  High
};
class DigitalLevel{
  digitalLevel value;

  const int RAISE_THRESHOLD = 600;
  const int FALL_THRESHOLD = 400;
  
  DigitalLevel(digitalLevel value){ this -> value = value; }

  public:
  static DigitalLevel Create(){ return  DigitalLevel( HorL_PULL ); }
  
  DigitalLevel Next(Voltage next_value){
    if(value == High){
      // 現在 High なら
      if( next_value.value < FALL_THRESHOLD )
        return  DigitalLevel(Low);
      return  DigitalLevel(High);
    }
    else{
      // 現在 Low なら
      if( next_value.value > RAISE_THRESHOLD )
        return  DigitalLevel(High);
      return  DigitalLevel(Low);
    }
  }
  digitalLevel GetValue(){ return value; }
};
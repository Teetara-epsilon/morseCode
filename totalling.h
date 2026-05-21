#ifndef TOTALLING_H
#define TOTALLING_H

class Totalling{
    public:
    unsigned int n;
    unsigned long totaltime;

    void ShowAve(){
        Serial.println("average time: ");
        Serial.println(totaltime/n);
    }
    void Show(){
        Serial.print("totaltime / average time: ");
        Serial.print(totaltime);
        Serial.print(" / ");
        Serial.print(totaltime/n);
        Serial.print("\n");
    }
};

#endif
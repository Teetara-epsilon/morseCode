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
};

#endif
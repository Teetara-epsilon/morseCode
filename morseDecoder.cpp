#include "morseDecoder.h"

MorseContext MorseDecoder::Decode(MorseElement element){
    static char pattern[7];   // ".-.-.-" まで入るサイズ。アルファベットだけなら4でも足りる
    static int patternLength = 0;

    static MorseContext outputQueue[8];
    static int queueHead = 0;
    static int queueTail = 0;
    static int queueCount = 0;

    auto enqueue = [&](MorseContext ctx){
        if(queueCount < 8){
            outputQueue[queueTail] = ctx;
            queueTail = (queueTail + 1) % 8;
            queueCount++;
        }
    };

    auto dequeue = [&]() -> MorseContext {
        if(queueCount == 0){
            return MorseContext();   // まだ出力文字なし
        }

        MorseContext ctx = outputQueue[queueHead];
        queueHead = (queueHead + 1) % 8;
        queueCount--;
        return ctx;
    };

    if(element == Dit){
        if(patternLength < 6){
            pattern[patternLength++] = '.';
        }
        else{
            patternLength = 0;
            enqueue(MorseContext('?', String(pattern)));
        }
    }
    else if(element == Dah){
        if(patternLength < 5){
            pattern[patternLength++] = '-';
        }
        else{
            patternLength = 0;
            enqueue(MorseContext('?', String(pattern)));
        }
    }
    else if(element == IntraGap){
        // 文字内の空白なので何もしない
    }
    else if(element == LetterGap){
        if(patternLength > 0){
            pattern[patternLength] = '\0';

            char decodedChar = DecodePattern(pattern);
            enqueue(MorseContext(decodedChar, String(pattern)));
            
            patternLength = 0;
        }
    }
    else if(element == WordGap){
        if(patternLength > 0){
            pattern[patternLength] = '_\0';
            char decodedChar = DecodePattern(pattern);
            enqueue(MorseContext(decodedChar, String(pattern)));
            patternLength = 0;
        }

        enqueue(MorseContext(' ', "/"));
    }
    else if(element == Invalid){
        // 無効入力は無視する
        // 厳密にしたいなら patternLength = 0; にしてもよい
    }

    return dequeue();
}

char MorseDecoder::DecodePattern(const char* pattern){
    Serial.print("DecodePattern: [");
    Serial.print(pattern);
    Serial.println("]");

    if(strcmp(pattern, ".-")   == 0) return 'A';
    if(strcmp(pattern, "-...") == 0) return 'B';
    if(strcmp(pattern, "-.-.") == 0) return 'C';
    if(strcmp(pattern, "-..")  == 0) return 'D';
    if(strcmp(pattern, ".")    == 0) return 'E';
    if(strcmp(pattern, "..-.") == 0) return 'F';
    if(strcmp(pattern, "--.")  == 0) return 'G';
    if(strcmp(pattern, "....") == 0) return 'H';
    if(strcmp(pattern, "..")   == 0) return 'I';
    if(strcmp(pattern, ".---") == 0) return 'J';
    if(strcmp(pattern, "-.-")  == 0) return 'K';
    if(strcmp(pattern, ".-..") == 0) return 'L';
    if(strcmp(pattern, "--")   == 0) return 'M';
    if(strcmp(pattern, "-.")   == 0) return 'N';
    if(strcmp(pattern, "---")  == 0) return 'O';
    if(strcmp(pattern, ".--.") == 0) return 'P';
    if(strcmp(pattern, "--.-") == 0) return 'Q';
    if(strcmp(pattern, ".-.")  == 0) return 'R';
    if(strcmp(pattern, "...")  == 0) return 'S';
    if(strcmp(pattern, "-")    == 0) return 'T';
    if(strcmp(pattern, "..-")  == 0) return 'U';
    if(strcmp(pattern, "...-") == 0) return 'V';
    if(strcmp(pattern, ".--")  == 0) return 'W';
    if(strcmp(pattern, "-..-") == 0) return 'X';
    if(strcmp(pattern, "-.--") == 0) return 'Y';
    if(strcmp(pattern, "--..") == 0) return 'Z';
    if(strcmp(pattern, ".-.-.-") == 0) return '.\n';
    if(strcmp(pattern, "--..--") == 0) return ', ';

    return '?';   // 未知のパターン
}
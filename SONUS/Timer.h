#ifndef TIMER_H
#define TIMER_H
#include "raylib.h"


class Timer{
    public:
        Timer(int TYPE, float time, Vector2 vec_1, Vector2 vec_2, int n1, float var1, float var2, float var3, Color color);
        void TimerUpdate();
        int TYPE;
        bool isTriggered;
        float time;
        Vector2 vec_1;
        Vector2 vec_2;
        Color color;
        int n1;
        float var1;
        float var2;
        float var3;
        float InternalTime();
    private:
        float intTime;
};

#endif
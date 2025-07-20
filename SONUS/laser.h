#ifndef LASER_H
#define LASER_H
#include "raylib.h"
class Laser{
    public:
        Laser(Vector2 pos, int w, float lenght, float duration, float rotation, Color color);
        void LaserUpdate();
        void LaserDraw();
        Vector2 pos;
        float duration;
        float rotation;
        Color color;
        bool active;
        bool dead;
        int w;
        float lenght;
        Vector2 point1;
        Vector2 point2;
    private:
};
#endif
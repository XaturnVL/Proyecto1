#ifndef BOOM_H
#define BOOM_H
#include "raylib.h"
class Boom{
public:
    Boom(Vector2 pos, float rot, float w, float radV, Color color);
    void BoomUpdate();
    void BoomDraw();
    Vector2 pos;
    Color color;
    float rad;
    float radV;
    float rot;
    float alpha;
    float rate;
    bool dead;
    float w;
private:
};
#endif
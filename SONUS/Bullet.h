#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

extern float BORDER_ARR;
extern float BORDER_ABJ;
extern float BORDER_DER;
extern float BORDER_IZQ;

class Bullet{
public:
    Bullet(Vector2 pos, Vector2 Vel, Vector2 Force, float thick, Color color);
    void Update();
    void Draw();
    Vector2 pos;
    Vector2 Vel;
    float thick;
    Color color;
    //Vector2 Points[15];
    Vector2 Force;
    bool dead;
    bool active;
private:
};

#endif
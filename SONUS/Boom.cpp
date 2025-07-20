#include "Boom.h"
#include <math.h>
Boom::Boom(Vector2 initPos, float boomRot, float boomW, float boomRadV, Color boomColor){
    dead = false;
    color = boomColor;
    pos = initPos;
    alpha = 0.5f;
    rate = 1.0;
    radV = boomRadV;
    rot = boomRot;
    w = boomW;
    if (w==0){w=10*PI;}
    rad = 0.0f;
}

void Boom::BoomUpdate(){
    float dt = GetFrameTime();

    rot += w*dt;
    rad += radV*dt;
    if (alpha==0){dead = true;}
    if (alpha > 0){
            if((alpha - rate*dt) < 0){alpha = 0;}
            else {alpha -= rate*dt;}
        }
}

void Boom::BoomDraw(){
    DrawPolyLinesEx(pos, 5, rad, rot, 5.0f, ColorAlpha(color, alpha));
}
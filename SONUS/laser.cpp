#include "Laser.h"
#include <math.h>

Laser::Laser(Vector2 initPos, int W, float LENGHT, float DURATION, float initRot, Color laserColor){
    active = true;
    dead = false;
    w = W;
    lenght = LENGHT;
    pos = initPos;
    color = laserColor;
    duration = DURATION;
    rotation = initRot;
    point1 = {pos.x + (lenght/2.0f)*cos(rotation), pos.y + (lenght/2.0f)*sin(rotation)};
    point2 = {pos.x - (lenght/2.0f)*cos(rotation), pos.y + (lenght/2.0f)*sin(rotation)};
}

void Laser::LaserUpdate(){
    float dt = GetFrameTime();
    rotation += (w*PI/180)*dt;
    point1 = {pos.x + (lenght/2.0f)*cos(rotation), pos.y + (lenght/2.0f)*sin(rotation)};
    point2 = {pos.x - (lenght/2.0f)*cos(rotation), pos.y + (lenght/2.0f)*sin(rotation)};
}

void Laser::LaserDraw(){
    DrawLineEx(point1, point2, 4.0f, color);
}
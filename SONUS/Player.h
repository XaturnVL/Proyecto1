#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

extern float BORDER_ARR;
extern float BORDER_ABJ;
extern float BORDER_DER;
extern float BORDER_IZQ;


class Player{
public:
    Player(Vector2 pos, Color color);
    void PlayerUpdate();
    void PlayerDraw();
    void PlayerReset();
    Vector2 pos;
    Color color;
    int life;
private:
    Vector2 Points[30];
    
};

#endif
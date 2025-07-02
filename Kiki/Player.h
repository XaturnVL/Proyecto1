#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player{
public:
    Player(Vector2 initPOS, Color playerColor, float playerRadius);
    void Update();
    void Draw();
    Vector2 Position;
    float speed;
    float radius;
    Color color;

private:
    
};

#endif
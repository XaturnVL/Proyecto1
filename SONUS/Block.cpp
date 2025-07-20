#include "Block.h"

Block::Block(Vector2 initPos, Color initColor){
    pos = initPos;
    color = initColor;
    rate = 1.0f;
    alpha = 0.5f;
    dead = false;
    active = true;
}

void Block::BlockUpdate(){
    float dt = GetFrameTime();
    if (alpha <= 0.0f){dead = true;}
    alpha -= rate*dt;
}

void Block::BlockDraw(){
    DrawRectangleV(pos, {60.0f,60.0f}, ColorAlpha(color,alpha));
}
#ifndef BLOCK_H
#define BLOCK_H
#include "raylib.h"

class Block{
public:
    Block(Vector2 pos, Color color);
    void BlockUpdate();
    void BlockDraw();
    float alpha;
    float rate;
    Vector2 pos;
    Color color;
    bool dead;
    bool active;

private:

};


#endif
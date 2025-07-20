#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

class Particle{
public:
    Particle(Vector2 pos, float v, float dir, float w, Color color);
    void ParticleUpdate();
    void ParticleDraw();
    Vector2 pos;
    float rot;
    float dir;
    float v;
    float w;
    Color color;
    float alpha;
    float rate;
    bool dead;
    
private:
    float vy;
};

#endif
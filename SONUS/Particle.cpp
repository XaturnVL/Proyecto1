#include "Particle.h"
#include <math.h>

Particle::Particle(Vector2 initPos, float particleVel, float particleDir, float particleRot, Color particleColor){
    pos = initPos;
    dir = particleDir;
    color = particleColor;
    w = particleRot;
    v = particleVel;
    rot = 0;
    vy = 0;
    alpha = 0.5;
    rate = 1.0;
    dead = false;

}

void Particle::ParticleUpdate(){
    float dt = GetFrameTime();
    pos.x += v*dt*cos(dir);
    pos.y += -v*dt*sin(dir) + vy*dt;
    vy+=500.0f*dt;
    rot += w*dt;
    if (alpha==0){dead = true;}
    if (alpha > 0){
            if((alpha - rate*dt) < 0){alpha = 0;}
            else {alpha -= rate*dt;}
        }
}


void Particle::ParticleDraw(){
    DrawPoly(pos, 6, 5.0f, rot, ColorAlpha(color,alpha));
}
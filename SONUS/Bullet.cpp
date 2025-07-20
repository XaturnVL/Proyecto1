#include "Bullet.h"
//int LONG = 15;
float BulletDead = 400;

Bullet::Bullet(Vector2 initPos, Vector2 initVel, Vector2 force, float Thick, Color BulletColor){
    active = true;
    dead = false;
    pos = initPos; //Posición inicial
    color = BulletColor; //Color inicial
    thick = Thick;
    Vel = initVel;
    Force = force;
    /*
    for (int i = 0; i < LONG; i++){
        Points[i] = initPos;
    }
    */
}

void Bullet::Update(){
    float dt = GetFrameTime();
    pos.x += Vel.x*dt;
    pos.y += Vel.y*dt;
    
    Vel.x += Force.x*dt;
    Vel.y += Force.y*dt;
    /*
    Points[LONG-1] = pos;
    for (int i = 0; i < LONG-1; i++){
        Points[i] = Points[i+1];
    }
    */

if (pos. x > BORDER_DER + BulletDead || pos.x < BORDER_IZQ - BulletDead){ dead = true;}
if (pos. y > BORDER_ABJ + (BulletDead-10) || pos.y < BORDER_ARR - (BulletDead-10)){ dead = true;}

}

void Bullet::Draw(){
    DrawCircleV(pos,7.0f, color);
    /*
    for (int i = 0; i < LONG-1; i++){
        DrawLineEx(Points[i],Points[i+1],thick,ColorAlpha(color,i/(LONG-2.0f)));
    }
    */
}
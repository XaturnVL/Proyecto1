#include "Player.h"
#include "raymath.h"
#include <math.h>



float r2 = 1/sqrt(2);
int Long = 30;
float v = 300.0f;
float PlayerGT = 15.0f;

float PSIZE = 11.0f;

Vector2 v1W = {0.0f,-2*PSIZE};
Vector2 v2W = {-1.2f*PSIZE,1.2f*PSIZE};
Vector2 v3W = {1.2f*PSIZE,1.2f*PSIZE};

Vector2 vertex1 = v1W;
Vector2 vertex2 = v2W;
Vector2 vertex3 = v3W;


Vector2 v1WD = Vector2Rotate(v1W,PI/4);
Vector2 v2WD = Vector2Rotate(v2W,PI/4);
Vector2 v3WD = Vector2Rotate(v3W,PI/4);

Vector2 v1WA = Vector2Rotate(v1W,-PI/4);
Vector2 v2WA = Vector2Rotate(v2W,-PI/4);
Vector2 v3WA = Vector2Rotate(v3W,-PI/4);

Vector2 v1A = Vector2Rotate(v1W,-PI/2);
Vector2 v2A = Vector2Rotate(v2W,-PI/2);
Vector2 v3A = Vector2Rotate(v3W,-PI/2);

Vector2 v1D = Vector2Rotate(v1W,PI/2);
Vector2 v2D = Vector2Rotate(v2W,PI/2);
Vector2 v3D = Vector2Rotate(v3W,PI/2);

Vector2 v1S = Vector2Rotate(v1W,PI);
Vector2 v2S = Vector2Rotate(v2W,PI);
Vector2 v3S = Vector2Rotate(v3W,PI);

Vector2 v1SA = Vector2Rotate(v1W,-0.75*PI);
Vector2 v2SA = Vector2Rotate(v2W,-0.75*PI);
Vector2 v3SA = Vector2Rotate(v3W,-0.75*PI);

Vector2 v1SD = Vector2Rotate(v1W,0.75*PI);
Vector2 v2SD = Vector2Rotate(v2W,0.75*PI);
Vector2 v3SD = Vector2Rotate(v3W,0.75*PI);

Player::Player(Vector2 initPos, Color PlayerColor){
    life = 0;
    pos = initPos; //Posición inicial
    color = PlayerColor; //Color inicial
    for (int i = 0; i < Long; i++){
        Points[i] = initPos;
    }    
}

void Player::PlayerUpdate(){
    float dt = GetFrameTime();

bool w = IsKeyDown(KEY_W);
bool a = IsKeyDown(KEY_A);
bool s = IsKeyDown(KEY_S);
bool d = IsKeyDown(KEY_D);
bool space = IsKeyDown(KEY_SPACE);
bool shift = IsKeyDown(KEY_LEFT_SHIFT);

if (space){v = 550;}
if (shift){v = 180;}
if (!space && !shift){v = 300;}

if ( w && !a && !s && !d ) {
    pos.y -= v*dt;

    vertex1=v1W; vertex2=v2W; vertex3=v3W;
}
else if ( !w &&  a && !s && !d ) {
    pos.x -= v*dt;

    vertex1=v1A; vertex2=v2A; vertex3=v3A;
}
else if ( !w && !a &&  s && !d ) {
    pos.y += v*dt;

    vertex1=v1S; vertex2=v2S; vertex3=v3S;
}
else if ( !w && !a && !s &&  d ) {
    pos.x += v*dt;

    vertex1=v1D; vertex2=v2D; vertex3=v3D;
}
else if ( w &&  a && !s && !d ) {
    pos.x -= r2*v*dt;
    pos.y -= r2*v*dt;

    vertex1=v1WA; vertex2=v2WA; vertex3=v3WA;
}
else if ( w && !a &&  s && !d ) {
    
}
else if ( w && !a && !s &&  d ) {
    pos.x += r2*v*dt;
    pos.y -= r2*v*dt;

    vertex1=v1WD; vertex2=v2WD; vertex3=v3WD;
}
else if ( !w &&  a &&  s && !d ) {
    pos.x -= r2*v*dt;
    pos.y += r2*v*dt;

    vertex1=v1SA; vertex2=v2SA; vertex3=v3SA;
}
else if ( !w &&  a && !s &&  d ) {
    
}
else if ( !w && !a &&  s &&  d ) {
    pos.x += r2*v*dt;
    pos.y += r2*v*dt;

    vertex1=v1SD; vertex2=v2SD; vertex3=v3SD;
}
else if ( w &&  a &&  s && !d ) {
    pos.x -= v*dt;

    vertex1=v1A; vertex2=v2A; vertex3=v3A;
}
else if ( w &&  a && !s &&  d ) {
    pos.y -= v*dt;

    vertex1=v1W; vertex2=v2W; vertex3=v3W;
}
else if ( w && !a &&  s &&  d ) {
    pos.x += v*dt;

    vertex1=v1D; vertex2=v2D; vertex3=v3D;
}
else if ( !w &&  a &&  s &&  d ) {
    pos.y += v*dt;

    vertex1=v1S; vertex2=v2S; vertex3=v3S;
}
else if ( w &&  a &&  s &&  d ) {
    
}
else {
    
}



//corección de posiciones en limites
if (pos.x + PSIZE > BORDER_DER){pos.x = BORDER_DER - PSIZE;}
if (pos.x - PSIZE< BORDER_IZQ){pos.x = BORDER_IZQ + PSIZE;}
if (pos.y + PSIZE > BORDER_ABJ){pos.y = BORDER_ABJ - PSIZE;}
if (pos.y - PSIZE < BORDER_ARR){pos.y = BORDER_ARR + PSIZE;}




    Points[Long-1] = pos;
    for (int i = 0; i < Long-1; i++){
        Points[i] = Points[i+1];
    }

}

void Player::PlayerDraw(){
    
    DrawTriangle(Vector2Add(pos,vertex1),Vector2Add(pos,vertex2),Vector2Add(pos,vertex3),color);
    for (int i = 0; i < Long-1; i++){
        DrawLineEx(Points[i],Points[i+1],i*PlayerGT/(Long-2.0f),color);
        DrawCircleV(Points[i],i*(PlayerGT/2)/(Long-2.0f),color);
    }
    
}

void Player::PlayerReset(){
    pos = {0.0f,0.0f};
    for (int i = 0; i < Long; i++){
        Points[i] = pos;
    }
    life = 0;
}
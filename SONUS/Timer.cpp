#include "Timer.h"
#include <math.h>
#include "Boom.h"
#include "Bullet.h"
#include <vector>
#include "Teleport.h"
#include "Block.h"
#include "Player.h"

using namespace std;
extern vector<Bullet> BULLETS;
extern vector<Boom> BOOMS;
extern vector<Teleport> TELEPORTS;
extern vector<Block> BLOCKS;
extern Player player;

extern float MUSIC_TIME;

Timer::Timer(int type, float Time, Vector2 Vec_1, Vector2 Vec_2, int N1, float Var1, float Var2, float Var3, Color obj_color){
    TYPE = type;
    isTriggered = false;
    time = Time;
    vec_1 = Vec_1;
    vec_2 = Vec_2;
    color = obj_color;
    n1 = N1;
    var1 = Var1;
    var2 = Var2;
    var3 = Var3;
    intTime = MUSIC_TIME;
}

void Timer::TimerUpdate(){
    float dt = GetFrameTime();
    intTime = MUSIC_TIME;
    if (intTime >= time && isTriggered==false){
        switch(TYPE){
            case 0:
                break;
            case 1: {
                BOOMS.push_back(Boom(vec_1, GetRandomValue(0,10)*2*PI/10, GetRandomValue(-1,1)*10*PI, 200.0f, color));
                for (int i = 0; i < n1; i++){
                //vec_1 = posición
                //var1 = velocidad
                //var2 = torque
                //var3 = angulo de rotación
                //n1 = numero de particulas
                float A1 = var3*PI/180.0f;
                BULLETS.push_back(Bullet(vec_1, {var1*cos(i*2*PI/n1 + A1),var1*sin(i*2*PI/n1 + A1)}, {var2*cos((i*2*PI/n1) + PI/4 + A1), var2*sin((i*2*PI/n1) + PI/4 + A1)}, 5.0f, color));   
                }
                break;
            }
            case 2: {
                BOOMS.push_back(Boom(vec_1, GetRandomValue(0,10)*2*PI/10, GetRandomValue(-1,1)*10*PI, 80.0f, player.color));
                TELEPORTS.push_back(Teleport(vec_1));
                break;
            }
            case 3: {
                float A2 = var2*PI/180.0f;
                BOOMS.push_back(Boom(vec_1, GetRandomValue(0,10)*2*PI/10, GetRandomValue(-1,1)*10*PI, 200.0f, color));
                BULLETS.push_back(Bullet(vec_1, {var1*cos(A2),var1*sin(A2)}, {var3*cos(A2 + PI/4),var3*sin(A2 + PI/4)}, 5.0f, color));
                break;
            }
            case 4: {
                BLOCKS.push_back(Block(vec_1, color));
                break;
            }
            case 5: {
                //vec_1 posición
                //var1 velocidad
                //n1 cantidad
                //var2 angulo inicial
                //var3 angulo final
                float gradA = (var3*PI/180.0f) - (var2*PI/180.0f);
                float dA = gradA/(n1 - 1);
                BOOMS.push_back(Boom(vec_1, GetRandomValue(0,10)*2*PI/10, GetRandomValue(-1,1)*10*PI, 200.0f, color));
                for(int i = 0; i < n1; i++){
                    float ang = (var2*PI/180.0f) + i*dA;
                    BULLETS.push_back(Bullet(vec_1, {var1*cos(ang),var1*sin(ang)}, {0.0f,0.0f}, 5.0f, color));
                }

                break;
            }
            case 6: {
                
            }

        }
        isTriggered = true;
    }
}

float Timer::InternalTime(){
    return intTime;
}
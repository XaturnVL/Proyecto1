#include "raylib.h"
#include "map.h"
#include "Particle.h"
#include "Player.h"
#include <vector>
#include "Bullet.h"
#include <math.h>
#include <algorithm>
#include <string>
#include "Boom.h"
#include "Timer.h"
#include "Teleport.h"
#include "Block.h"
#include "csv.h"
#include "utils.h"

using namespace std;
using namespace io;

Texture2D MapBackground;

float alphaFade;
bool PAUSE;

bool shaderExists;
bool backgroundExists;
Shader shader;
int resolutionLoc;
int timeLoc;
float resolution[2] = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };


float MUSIC_TIME;

Music musicMap;

Timer timerControl = Timer(0,100.0f,{0,0},{0,0},0, 0,0,0,BLACK);

Player player = Player({0.0f,0.0f},WHITE);

vector<Boom> BOOMS;
vector<Particle> PARTICLES;
vector<Bullet> BULLETS;
vector<Timer> TIMERS;
vector<Timer> TIMER_SOURCE;
vector<Teleport> TELEPORTS;
vector<Block> BLOCKS;

void InitScene1(string MAP_NAME){
    PAUSE = false;
    alphaFade = 1.0f;
    MUSIC_TIME = 0.0f;

    string SHADER_PATH = "maps/" + MAP_NAME + "/map_shader.fs";
    shaderExists = FileExists(SHADER_PATH.c_str());

    if (shaderExists){

    shader = LoadShader(0, SHADER_PATH.c_str());
    resolutionLoc = GetShaderLocation(shader, "iResolution");
    timeLoc = GetShaderLocation(shader, "iTime");
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    }

    string BACKGROUND_PATH = "maps/" + MAP_NAME + "/map_background.png";
    backgroundExists = FileExists(BACKGROUND_PATH.c_str());

    if (backgroundExists){
        MapBackground = LoadTexture(BACKGROUND_PATH.c_str());
    }
    

    string MUSIC_PATH = "maps/" + MAP_NAME + "/map_song.mp3";
    SetRandomSeed(69);
    player.pos = {0,0};
    musicMap = LoadMusicStream(MUSIC_PATH.c_str());
    

    string OBJ_PATH = "maps/" + MAP_NAME + "/map.csv";
    CSVReader<14> in(OBJ_PATH.c_str());
    in.read_header(ignore_extra_column,"type","time","x1","y1","x2","y2","n1","var1","var2","var3","red","green","blue","alpha");
    int csv_type; float csv_time; float csv_x1; float csv_y1; float csv_x2; float csv_y2; int csv_n1; float csv_var1; float csv_var2; float csv_var3; int csv_red; int csv_green; int csv_blue; int csv_alpha;
    while(in.read_row(csv_type,csv_time,csv_x1,csv_y1,csv_x2,csv_y2,csv_n1,csv_var1,csv_var2,csv_var3,csv_red,csv_green,csv_blue,csv_alpha)){
        TIMER_SOURCE.push_back(Timer(csv_type, csv_time, {csv_x1,csv_y1}, {csv_x2,csv_y2}, csv_n1, csv_var1, csv_var2, csv_var3, {csv_red, csv_green, csv_blue, csv_alpha}));
    }
    TIMERS = TIMER_SOURCE;
}

void UpdateScene1(){
    if (IsKeyPressed(KEY_R)){ResetMap();}
    float time = (float)GetTime();
    float dt = GetFrameTime();
    if (shaderExists){SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);}
    if (!IsMusicStreamPlaying(musicMap)){PlayMusicStream(musicMap);}
    MUSIC_TIME = GetMusicTimePlayed(musicMap);
    UpdateMusicStream(musicMap);  
    player.PlayerUpdate();
    for (auto& p : PARTICLES){p.ParticleUpdate();}
    for (auto& b : BOOMS){b.BoomUpdate();}
    for (auto& T : TELEPORTS){T.TeleportUpdate();}
    timerControl.TimerUpdate();
    for (auto& t : TIMERS){t.TimerUpdate();}
    for (auto& b : BULLETS){b.Update();}
    for (auto& b : BLOCKS){b.BlockUpdate();}

    //remover blocks muertos
    BLOCKS.erase(
    remove_if(BLOCKS.begin(), BLOCKS.end(),
        [](const Block& b) {
            return b.dead;
        }),
    BLOCKS.end());


    //remover balas muertas
    BULLETS.erase(
    remove_if(BULLETS.begin(), BULLETS.end(),
        [](const Bullet& b) {
            return b.dead;
        }),
    BULLETS.end());

    //remover particulas muertas
    PARTICLES.erase(
    remove_if(PARTICLES.begin(), PARTICLES.end(),
        [](const Particle& p) {
            return p.dead;
        }),
    PARTICLES.end());

    //remover booms muertos
    BOOMS.erase(
    remove_if(BOOMS.begin(), BOOMS.end(),
        [](const Boom& b) {
            return b.dead;
        }),
    BOOMS.end());

    //remover teleports activados
    TELEPORTS.erase(
    remove_if(TELEPORTS.begin(), TELEPORTS.end(),
        [](const Teleport& t) {
            return t.isTel;
        }),
    TELEPORTS.end());



    //Verificador de daño al jugador
    for (auto& b : BULLETS){
        if(CheckCollisionCircles(player.pos, 11.0f, b.pos, 7.0f) && b.active==true){
            for (int i=1; i<=10; i++){PARTICLES.push_back(Particle(player.pos, 250.0f, GetRandomValue(0, 100)*2*PI/100, 10*PI, player.color));}
            b.active=false;
            player.life+=1;}       
        }

    for (auto& b : BLOCKS){
        if(CheckCollisionCircleRec(player.pos, 11.0f, {b.pos.x, b.pos.y, 60.0f, 60.0f}) && b.active==true){
            for (int i=1; i<=10; i++){PARTICLES.push_back(Particle(player.pos, 250.0f, GetRandomValue(0, 100)*2*PI/100, 10*PI, player.color));}
            b.active=false;
            player.life+=1;}       
        }

    if (alphaFade>0){alphaFade-=1.5f*dt;}

    



}

void DrawScene1(){
    if (shaderExists){
        BeginShaderMode(shader);
        DrawRectangle(-SCREEN_WIDTH/2.0f, -SCREEN_HEIGHT/2.0f, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
        EndShaderMode();
    }
    
    if (backgroundExists){
        DrawTextureC(MapBackground, {0.0f,0.0f}, SCREEN_WIDTH/MapBackground.width, 0.0f, ColorAlpha(WHITE,0.5f));
    }
    
    

    //dibujado de objetos
    player.PlayerDraw();

    for (auto& b : BOOMS){b.BoomDraw();}

    for (auto& p : PARTICLES){p.ParticleDraw();}

    for (auto& b : BULLETS){b.Draw();}

    for (auto& b : BLOCKS){b.BlockDraw();}


    //dibujado sombra del mapa
    DrawRectangle(-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, SCREEN_WIDTH, 60, ColorAlpha(BLACK,0.6f));
    DrawRectangle(-SCREEN_WIDTH/2, 300 , SCREEN_WIDTH, 60, ColorAlpha(BLACK,0.6f));
    DrawRectangle(-SCREEN_WIDTH/2, -300 , 340, 600, ColorAlpha(BLACK,0.6f));
    DrawRectangle(300, -300 , 340, 600, ColorAlpha(BLACK,0.6f));

    //dibujado del border
    DrawRectangleLinesEx({BORDER_IZQ,BORDER_ARR,BORDER_DER-BORDER_IZQ,BORDER_ABJ-BORDER_ARR}, 2.0f, BORDER_COLOR);  

}

void DrawGUIScene1(){
    string HITS_TXT = "Hits: " + to_string(player.life);
    DrawText(HITS_TXT.c_str(), 0, 0, 40, WHITE);  
    DrawText(to_string(timerControl.InternalTime()).c_str(), 0, 50, 40, WHITE);  
    DrawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, ColorAlpha(BLACK,alphaFade));
}

void UnloadScene1(){
    ResetMap();

    if (shaderExists){UnloadShader(shader);}
    StopMusicStream(musicMap);
    UnloadMusicStream(musicMap);
    
    TIMERS.clear();
}

void ResetMap(){
    alphaFade = 1.0f;
    TIMERS.clear();
    BULLETS.clear();
    BOOMS.clear();
    BLOCKS.clear();
    PARTICLES.clear();
    TELEPORTS.clear();
    player.PlayerReset();
    MUSIC_TIME = 0.0f;
    SeekMusicStream(musicMap, 0.0f);
    WaitTime(1.0f);
    TIMERS = TIMER_SOURCE;
}
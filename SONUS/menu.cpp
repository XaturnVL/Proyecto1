#include "menu.h"
#include "raymath.h"
#include "selector.h"
#include "utils.h"
#include <math.h>
using namespace std;

Font GameFont;

float CHANGE_SCENE_TIMER; //Es el timer que empieza a contar el tiempo al presionar el botón de Play
bool CHANGIN_SCENE; //Se activa al darle click al botón de Play

Music menuMusic; //Musica del menú
Sound button_sfx; //Efecto de sonido del botón
float Pscale; //Escala del botón



Shader menu_shader; //Shader del fondo
//Todas las variables del Shader
int menu_resolutionLoc; 
int menu_timeLoc;
float menu_resolution[2] = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };


const int LONG_MOUSE = 10; //Longitud del rastro del mouse
Vector2 MouseTrailPoints[LONG_MOUSE]; //Vector de los puntos que deja el rastro del mouse

float menuAlpha; //Transición al iniciar el juego

Vector2 MousePos; //Posición del mouse en pantalla la camara

Texture2D PlayButton; //Textura del botón de Play

void InitScene0(){

    Pscale = 0.2f;
    CHANGE_SCENE_TIMER = 0;
    CHANGIN_SCENE = false;
    PlayButton = LoadTexture("res/play_button.png");
    menuMusic = LoadMusicStream("res/menu_music.mp3");
    button_sfx = LoadSound("res/button_effect.wav");
    GameFont = LoadFontEx("res/GameFont.otf", 200, 0, 0);
    
    menuAlpha = 1.0f;
    menu_shader = LoadShader(0, "res/menuShader.fs");
    menu_resolutionLoc = GetShaderLocation(menu_shader, "iResolution");
    menu_timeLoc = GetShaderLocation(menu_shader, "iTime");
    SetShaderValue(menu_shader, menu_resolutionLoc, menu_resolution, SHADER_UNIFORM_VEC2);
    PlayMusicStream(menuMusic);

    for (int i = 0; i < LONG_MOUSE; i++){
        MouseTrailPoints[i] = GetMousePosition();
    }
}

void UpdateScene0(){
    if (IsKeyPressed(KEY_F11)){
        ToggleFullscreen();
    }
    float time = (float)GetTime();
    MousePos = {(GetMousePosition().x - SCREEN_WIDTH/2), (GetMousePosition().y - SCREEN_HEIGHT/2)};

    float dt = GetFrameTime();
    SetShaderValue(menu_shader, menu_timeLoc, &time, SHADER_UNIFORM_FLOAT);

    UpdateMusicStream(menuMusic);

    if (menuAlpha > 0){
            if((menuAlpha - 0.2*dt) < 0){menuAlpha = 0;}
            else {menuAlpha -= 0.2*dt;}
        }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(MousePos,{0,0},120.0f)){
        PlaySound(button_sfx);
        CHANGIN_SCENE = true;
    }


    if(CHANGIN_SCENE){CHANGE_SCENE_TIMER+=dt; Pscale+=0.4*dt;}



    MouseTrailPoints[LONG_MOUSE-1] = GetMousePosition();
    for (int i = 0; i < LONG_MOUSE-1; i++){
        MouseTrailPoints[i] = MouseTrailPoints[i+1];
    }

    if (CHANGE_SCENE_TIMER >= 1.5f){
        UnloadScene0();
        InitScene2();
        GAME_SCENE = 2;
    }
}

void DrawScene0(){
    BeginShaderMode(menu_shader);
        DrawRectangle(-SCREEN_WIDTH/2.0f - 500, -SCREEN_HEIGHT/2.0f - 500, SCREEN_WIDTH + 500, SCREEN_HEIGHT + 500, WHITE);
    EndShaderMode();
    float PlayButtonRot = (2*PI)*sin(2*PI*GetTime()/1.5f);
    DrawTextureC(PlayButton, {0.0f,0.0f}, Pscale, PlayButtonRot, WHITE);
    
    DrawTextC(GameFont, "SONUS", {0,-0.7*SCREEN_HEIGHT/2.0f}, 70, 1, WHITE);
    
}

void DrawGUIScene0(){
    DrawText("alpha v0.1", 0, 0, 20, WHITE);
    DrawRectangle(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BLACK,menuAlpha));
    for (int i = 0; i < LONG_MOUSE; i++){
        DrawCircleV(MouseTrailPoints[i],5.0f,ColorAlpha(WHITE,i/(LONG_MOUSE-2.0f)));
    }
    DrawCircleV(GetMousePosition(),5.0f,WHITE);
    if(CHANGIN_SCENE){DrawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, ColorAlpha(BLACK,2*CHANGE_SCENE_TIMER));}
}

void UnloadScene0(){
    StopMusicStream(menuMusic);
    UnloadMusicStream(menuMusic);
    UnloadSound(button_sfx);
    UnloadShader(menu_shader);
    UnloadFont(GameFont);  
    UnloadTexture(PlayButton);
}
#include <iostream>
#include <raylib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "menu.h"
#include "map.h"
#include "selector.h"
#include "utils.h"

using namespace std;

Texture2D LOGO;

int GAME_SCENE;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

float BORDER_ARR = -300.0f;
float BORDER_ABJ = 300.0f;
float BORDER_DER = 300.0f;
float BORDER_IZQ = -300.0f;

void GameDraw();
void GameUpdate();
void GameDrawGUI();

Color BORDER_COLOR = RED;
Camera2D camara = {0}; //Objeto camara del juego




int main () {
    
    GAME_SCENE = 0;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SONUS");
    SetTargetFPS(75);
    HideCursor();
    camara.offset = {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f}; //Mueve la camara al centro de la ventana
    camara.zoom = 1.0f;
    LOGO = LoadTexture("res/xquare.png");
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
    InitAudioDevice();
    InitScene0();


    
    while (WindowShouldClose() == false){

        GameUpdate();
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camara);
        GameDraw();
        EndMode2D();
        GameDrawGUI();
        EndDrawing();
        
    }
    switch(GAME_SCENE){
        case 0: UnloadScene0(); break;
        case 1: UnloadScene1(); break;
        case 2: UnloadScene2(); break;
    } 
    CloseAudioDevice();
    CloseWindow();
}


void GameUpdate(){
switch(GAME_SCENE){
    case 0: UpdateScene0(); break;
    case 1: UpdateScene1(); break;
    case 2: UpdateScene2(); break;
}
}



void GameDraw(){
switch(GAME_SCENE){
    case 0: DrawScene0(); break;
    case 1: DrawScene1(); break;
    case 2: DrawScene2(); break;
}
}




void GameDrawGUI(){
switch(GAME_SCENE){
    case 0: DrawGUIScene0(); break;
    case 1: DrawGUIScene1(); break;
    case 2: DrawGUIScene2(); break;
}
}


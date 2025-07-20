#include "selector.h"
#include "MapWin.h"
#include "utils.h"
#include <math.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include "map.h"
using namespace std;
namespace fs = std::filesystem;

Font GAMEFONT;
float selectorAlpha;
Sound play_sfx;

string pathMaps = "maps";
int MapCount;
vector<string> MapsNames;
vector<MapWin> MAPWINS;
vector<Music> SONGS;
vector<Texture2D> BACKGROUNDS;


float alphaToMap;
bool changingToMap;

int SelectedMap = 0;
float MapDist = 40.0f;



vector<string> getMapsList(const string& rutaMaps){
    vector<string> nombreCarpetas;
    try{
        for (const auto& entrada : fs::directory_iterator(rutaMaps)){
            if (fs::is_directory(entrada.status())){
                nombreCarpetas.push_back(entrada.path().filename().string());
            }
        }
    } catch (const fs::filesystem_error& e) {

    }
    return nombreCarpetas;
}

void InitScene2(){
    changingToMap = false;
    alphaToMap = 0.0f;

    GAMEFONT = LoadFontEx("res/GameFont.otf", 200, 0, 0);
    selectorAlpha = 1.0f;
    MapsNames = getMapsList(pathMaps);
    MapCount = MapsNames.size();
    for (int i = 0; i < MapCount; i++){
        string MapBackgroundPath = "maps/" + MapsNames[i] + "/map_background.png";
        string MapSongPath = "maps/" + MapsNames[i] + "/map_song.mp3";
        BACKGROUNDS.push_back(LoadTexture(MapBackgroundPath.c_str()));
        SONGS.push_back(LoadMusicStream(MapSongPath.c_str()));
    }
    for (int i = 0; i < MapCount; i++){MAPWINS.push_back(MapWin({0.0f,i*MapDist}, 20.0f, WHITE, MapsNames[i], GAMEFONT));}
    
    PlayMusicStream(SONGS.at(0));
}

void UpdateScene2(){
    float dt = GetFrameTime();
    if (selectorAlpha > 0){
            if((selectorAlpha - 0.5*dt) < 0){selectorAlpha = 0;}
            else {selectorAlpha -= 0.5*dt;}
        }
    UpdateMusicStream(SONGS.at(SelectedMap));

    if (IsKeyPressed(KEY_DOWN) && SelectedMap < (MapCount-1)){StopMusicStream(SONGS[SelectedMap]); SelectedMap+=1; PlayMusicStream(SONGS[SelectedMap]);}
    if (IsKeyPressed(KEY_UP) && SelectedMap > 0){StopMusicStream(SONGS[SelectedMap]); SelectedMap-=1; PlayMusicStream(SONGS[SelectedMap]);}


    for (auto& m : MAPWINS){m.pos.y = m.INIT_POS.y - SelectedMap*MapDist;}
    
    for (int i = 0; i < MapCount; i++){
        if (i == SelectedMap){MAPWINS[i].scale = 30.0f; MAPWINS[i].color = RED;}
        else {MAPWINS[i].scale = 20.0f; MAPWINS[i].color = WHITE;}
    }





    if (alphaToMap>=1.0f){
        InitScene1(MapsNames[SelectedMap]);
        UnloadScene2();
        GAME_SCENE = 1;
    }

    if (changingToMap){
        alphaToMap += 2.0*dt;
    }

    if (IsKeyPressed(KEY_ENTER)){
        changingToMap = true;
    }

}

void DrawScene2(){
    DrawTextureC(BACKGROUNDS[SelectedMap], {0.0f,0.0f}, SCREEN_WIDTH/BACKGROUNDS[SelectedMap].width, 0.0f, ColorAlpha(WHITE,0.5f));
    DrawRectangleC({0,0}, 400.0f, SCREEN_HEIGHT, 0.0f, ColorAlpha(BLACK,0.5f));
    for (auto& m : MAPWINS){m.DrawMapWin();}
}

void DrawGUIScene2(){
    DrawText(to_string(SelectedMap).c_str(), 0, 0, 40, WHITE);
    DrawRectangle(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BLACK,selectorAlpha));
    DrawRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BLACK, alphaToMap));
}

void UnloadScene2(){
    StopMusicStream(SONGS[SelectedMap]);
    for (auto& b : BACKGROUNDS) {UnloadTexture(b);}
    for (auto& m : SONGS) {UnloadMusicStream(m);}
}
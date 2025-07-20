#ifndef SCENE0_H
#define SCENE0_H
#include "raylib.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern Camera2D camara;
extern int GAME_SCENE;

void InitScene0();

void UpdateScene0();

void DrawScene0();

void DrawGUIScene0();

void UnloadScene0();

#endif 
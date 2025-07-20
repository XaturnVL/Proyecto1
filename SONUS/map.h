#ifndef SCENE1_H
#define SCENE1_H
#include <string>

extern float BORDER_ARR;
extern float BORDER_ABJ;
extern float BORDER_DER;
extern float BORDER_IZQ;
extern Color BORDER_COLOR;

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

void InitScene1(std::string MAP_NAME);

void UpdateScene1();

void DrawScene1();

void DrawGUIScene1();

void UnloadScene1();

void ResetMap();


#endif 
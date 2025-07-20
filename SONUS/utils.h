#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"

void DrawTextureC(Texture2D Textura, Vector2 Origen, float scale, float rotation, Color color);

void DrawTextC(Font font, const char *text, Vector2 pos, float fontSize, float spacing, Color tint);

void DrawRectangleC(Vector2 pos, float width, float height, float rotation, Color color);

#endif
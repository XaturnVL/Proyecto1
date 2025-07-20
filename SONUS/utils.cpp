#include "utils.h"

void DrawTextureC(Texture2D Textura, Vector2 Origen, float scale, float rotation, Color color){
    Rectangle dstRec = {Origen.x, Origen.y, Textura.width * scale, Textura.height * scale};
    DrawTexturePro(Textura, {0,0,Textura.width, Textura.height}, dstRec, {dstRec.width/2.0f,dstRec.height/2.0f}, rotation, color);
}

void DrawTextC(Font font, const char *text, Vector2 pos, float fontSize, float spacing, Color tint) {
    // 1. Mide el tamaño del texto
    Vector2 size = MeasureTextEx(font, text, fontSize, spacing);
    // 2. Calcula el origen como la mitad del tamaño (ancho y alto)
    Vector2 origin = { size.x * 0.5f, size.y * 0.5f };
    // 3. Dibuja usando DrawTextPro centrando en pos
    DrawTextPro(font, text, pos, origin, 0.0f, fontSize, spacing, tint);
}

void DrawRectangleC(Vector2 pos, float width, float height, float rotation, Color color) {
    Rectangle rec = {
        pos.x,
        pos.y,
        width,
        height
    };
    Vector2 origin = { width*0.5f, height*0.5f };
    DrawRectanglePro(rec, origin, rotation, color);
}
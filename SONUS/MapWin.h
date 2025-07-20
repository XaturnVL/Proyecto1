#ifndef MAPWIN_H
#define MAPWIN_H
#include "raylib.h"
#include <string>

using namespace std;

class MapWin{
    public:
        MapWin(Vector2 pos, float scale, Color color, string mapname, Font font);
        void UpdateMapWin();
        void DrawMapWin();
        Vector2 INIT_POS;
        Vector2 pos;
        float scale;
        Color color;
        string mapname;
        Font font;
    private:

};

#endif
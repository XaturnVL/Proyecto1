#include "MapWin.h"
#include "utils.h"


MapWin::MapWin(Vector2 initPos, float initScale, Color mapColor, string mapName, Font winFont){
    pos = initPos;
    scale = initScale;
    color = mapColor;
    INIT_POS = initPos;
    font = winFont;
    mapname = mapName;
}

void MapWin::UpdateMapWin(){

}

void MapWin::DrawMapWin(){
    DrawTextC(font, mapname.c_str(),pos, scale, 1, color);
}
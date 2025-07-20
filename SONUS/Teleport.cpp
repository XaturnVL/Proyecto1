#include "Teleport.h"
#include "Player.h"

extern Player player;

Teleport::Teleport(Vector2 TelPos){
    posTel = TelPos;
    isTel = false;
}

void Teleport::TeleportUpdate(){
    if(isTel == false){player.pos = posTel; isTel = true;}
}
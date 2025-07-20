#ifndef TELEPORT_H
#define TELEPORT_H
#include "raylib.h"

class Teleport{
    public:
        Teleport(Vector2 posTel);
        void TeleportUpdate();
        Vector2 posTel;
        bool isTel;
    private:
};

#endif
#include "Player.h"

//Clase del jugador

Player::Player(Vector2 initPOS, Color playerColor, float playerRadius){
    Position = initPOS; //Posición inicial
    color = playerColor; //Color inicial
    radius = playerRadius; //Radio
    speed = 0.0f; //Velocidad inicial
}

void Player::Update(){
    float dt = GetFrameTime();
    Position.y += speed * dt; //Caida


    speed += 60.0f * dt; //Gravedad

    //Salto
    if(IsKeyPressed(KEY_SPACE)){
        speed = -30.0f;
    }
}

//Dibujar jugador
void Player::Draw(){
    DrawCircleV(Position, radius, color);
}
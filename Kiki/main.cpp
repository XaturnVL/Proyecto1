#include <iostream>
#include <raylib.h>
#include <cmath>
#include "Player.h"

using namespace std;

//====================================================================================
                    //              ZONA DE PRUEBAS                            
//====================================================================================



float var = 255;




//====================================================================================
//====================================================================================






//------------ DECLARA FUNCIONES PRINCIPALES DEL JUEGO ------------
void Update(float dt); //Función que se ejecuta en cada frame del juego
void Draw(); //Dibuja objetos en el mundo
void DrawGUI(); //Dibuja objetos de interfaz sobre la pantalla (Menú, Botones, Puntos, etc)

//Rango de la camara del juego  -->  x: (-18 , 18)   y: (-32 , 32)


//------------ Inicializa datos importantes ------------
Player Bola({0.0f,0.0f}, RED, 2.0f); //Objeto jugador
Camera2D camara = {0}; //Objeto camara del juego
Vector2 CamPos; //Posición de la camara en el mundo
float dist; //Distancia entre el jugador y la camara (sirve para acomodar la camara y que siga al jugador cuando suba)
const float DIST_MAX = 20.0f; //Distancia máxima que puede haber entre el jugador y la camara


int main () {

    //------------ Inicializa el juego ------------
    const int RESOLUTION = 40; //Resolución de la ventana del juego
    const int SCREEN_WIDTH = 9*RESOLUTION; //Ancho de la ventana
    const int SCREEN_HEIGHT = 16*RESOLUTION; //Alto de la ventana
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Kiki"); //Crea la ventana
    SetTargetFPS(60); //Establece los FPS del juego

    camara.offset = {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f}; //Mueve la camara al centro de la ventana
    camara.zoom = 10.0f; //Agrega zoom a la camara para ver más de cerca los objetos del mundo
    CamPos = {0,0}; //Establece la posición inicial de la camara (en el centro del mundo)


    //------------ Bucle principal del juego ------------
    while (WindowShouldClose() == false){

        float deltaTime = GetFrameTime(); //Lapso de tiempo entre cada frame
        Update(deltaTime); //Ejecuta la función Update que se ejecuta a cada frame

        BeginDrawing(); //Inicia el dibujado
        ClearBackground(SKYBLUE); //Establece el color del fondo

        DrawGUI(); //Dibuja los elementos de la interfaz

        BeginMode2D(camara); //Inicia el dibujado del mundo
            Draw(); //Dibuja los objetos del mundo
        EndMode2D(); //Termina el dibujado del mundo

        EndDrawing(); //Termina el dibujado
    }
    

    CloseWindow(); //Cierra la ventana
}


void Update(float dt){
    
    Bola.Update(); //Actualiza el objeto jugador

    //------------ Ajustar la camara según altura de la bola ------------
    dist = CamPos.y - Bola.Position.y; 
    if(dist > DIST_MAX){
        CamPos.y = Bola.Position.y + DIST_MAX;
        camara.offset.y = (-CamPos.y + 32.0f)*camara.zoom;

    }



    var = 255.0f*cos(0.5f*GetTime());




}

void Draw(){
    
    Bola.Draw(); //Dibuja la bola

    DrawLineV({-18.0f,0.0f},{18.0f,0.0f},WHITE); //eje x
    DrawLineV({0.0f,32.0f},{0.0f,-32.0f},WHITE); //eje y
}

void DrawGUI(){
    //------------ Dibuja la altura del jugador ------------
    string hStr = to_string((int) -Bola.Position.y); //Convierte numero altura en texto
    DrawText(hStr.c_str(), 0, 0, 40, WHITE);  //Dibuja el texto de altura

    DrawFPS(0,600);
    
}
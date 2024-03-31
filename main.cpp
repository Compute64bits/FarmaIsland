#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#include "raylib.h"

int window_w = 1080;
int window_h = 720;
int fps = 60;

Vector2 move(Vector2 pos, Vector2 dest, int speed){
    Vector2 final = pos;

    if(pos.x < dest.x) final.x += speed;
    else if(pos.x > dest.x) final.x -= speed;  

    if(pos.y < dest.y) final.y += speed;
    else if(pos.y > dest.y) final.y -= speed;

    return final;
}

int main(void){
    InitWindow(window_w, window_h, "FarmaIsland");
    SetTargetFPS(fps);

    Texture2D grassPlus = LoadTexture("assets/GRASS+.png");
    Rectangle gp_grass_1 = { 0.0f, 0.0f, 16.0f, 16.0f};
    Rectangle gp_grass_2 = { 0.0f, 4*16.0f, 16.0f, 16.0f};
    Rectangle gp_grass_3 = { 2*16.0f, 4*16.0f, 16.0f, 16.0f};
    Rectangle gp_grass_4 = { 6*16.0f, 2*16.0f, 16.0f, 16.0f};
    Rectangle gp_grass_5 = { 2*16.0f, 6*16.0f, 16.0f, 16.0f};

    Texture2D charac = LoadTexture("assets/player.png");
    Rectangle cc_face = { 0.0f, 0.0f, 32.0f, 64.0f};

    Vector2 human_pos = {500.0f, 250.0f};
    Vector2 point_pos = {-300.0f, -300.0f};
    bool point_stat = false;

    std::vector<int> maps;
    for (int i=0; i<=(window_h/16+1)*(window_w/16+1); i++){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 4);  
        maps.push_back(distrib(gen));
    }

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            point_stat = true;
            point_pos = GetMousePosition();
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            point_stat = false;
        }

        if(point_stat){
            human_pos = move(human_pos, point_pos, 1);
            if(human_pos.x == point_pos.x && human_pos.y == point_pos.y) point_stat = false;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            int i = 0;
            for (float y=0; y<=window_h; y+=16){
                for (float x=0; x<=window_w; x+=16){
                    if(maps[i]==0) DrawTexturePro(grassPlus, gp_grass_1, (Rectangle){x, y, 32.0f, 32.0f}, {16.0f, 16.0f}, 0.0, WHITE);
                    else if(maps[i]==1) DrawTexturePro(grassPlus, gp_grass_2, (Rectangle){x, y, 32.0f, 32.0f}, {16.0f, 16.0f}, 0.0, WHITE);
                    else if(maps[i]==2) DrawTexturePro(grassPlus, gp_grass_3, (Rectangle){x, y, 32.0f, 32.0f}, {16.0f, 16.0f}, 0.0, WHITE);
                    else if(maps[i]==3) DrawTexturePro(grassPlus, gp_grass_4, (Rectangle){x, y, 32.0f, 32.0f}, {16.0f, 16.0f}, 0.0, WHITE);
                    else if(maps[i]==4) DrawTexturePro(grassPlus, gp_grass_5, (Rectangle){x, y, 32.0f, 32.0f}, {16.0f, 16.0f}, 0.0, WHITE);
                    i++;
                }
            }

            if (point_stat) DrawText("x", point_pos.x-5, point_pos.y-10, 20, LIGHTGRAY);
            
            DrawTexturePro(charac, cc_face, (Rectangle){human_pos.x-15, human_pos.y, 64.0f, 128.0f}, {32.0f, 64.0f}, 0.0, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
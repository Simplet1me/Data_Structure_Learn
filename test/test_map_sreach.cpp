#include "raylib.h"
#include "map_sreach.hpp"
#include <iostream>
#include <string>

int main(){
    const int x = 180;
    const int y = 99;
    const float size = 10;
    const int dx = 50;
    const int dy = 50;

    std::pair<int,int> start = {1,1};
    std::pair<int,int> end = {175,95};

    Map map(x,y,size);
    map.summonMaze(1,1,175,95,5,20,40);

    auto astar_path = map.astarSreach(start,end);
    auto bfspath = map.bfsSreach(start,end);

    std::vector<std::vector<int>> okpMap = map.getMap();
    
    // raylib
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib demo");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("bfs:YELLOW",50,10,40,YELLOW);
        DrawText("astart:GREEN",500,10,40,GREEN);

        // 绘制网格地图
        float cellSize = map.size;
        for (int index_y = 0; index_y < map.height; index_y++){
            for (int index_x = 0; index_x < map.width; index_x++){
                float x = dx + index_x * cellSize;
                float y = dy + index_y * cellSize;
                DrawRectangleLines((int)x, (int)y, (int)cellSize, (int)cellSize, BLACK);
                if (okpMap[index_x][index_y] == 1){
                    DrawRectangle( dx + index_x * cellSize, dy + index_y * cellSize, (int)map.size, (int)map.size, BLACK);
                }
            }
        }

        for (auto p : astar_path){
            DrawRectangle( dx + p.first * cellSize, dy + p.second * cellSize, (int)map.size, (int)map.size, GREEN);
        }

        for (auto p : bfspath){
            DrawRectangle(dx + p.first * cellSize, dy + p.second * cellSize, (int)map.size, (int)map.size, YELLOW);
        }

        DrawRectangle( dx + 1 * cellSize, dy + 1 * cellSize, (int)map.size, (int)map.size, RED);
        DrawRectangle( dx + 175 * cellSize, dy + 95 * cellSize, (int)map.size, (int)map.size, RED);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
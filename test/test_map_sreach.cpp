#include "raylib.h"
#include "map_sreach.hpp"
#include <algorithm>
#include <iostream>
#include <string>

// 复选框更新函数
bool UpdateCheckbox(Rectangle box, bool checked){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), box)){
        return !checked;
    }
    return checked;
}

// 按钮点击检测函数
bool IsButtonClicked(Rectangle buttonRect){
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), buttonRect);
}

// 复选框绘制函数
void DrawCheckbox(Rectangle box, bool &checked, const char *text, Color textColor){
    DrawRectangleRec(box, WHITE);
    DrawRectangleLinesEx(box, 2, DARKGRAY);

    // √绘制部分
    if (checked){
        DrawLine((int)box.x + 4, (int)box.y + 14, (int)box.x + 11, (int)box.y + 22, BLACK);
        DrawLine((int)box.x + 11, (int)box.y + 22, (int)box.x + 24, (int)box.y + 6, BLACK);
    }

    // 文本绘制
    DrawText(text, (int)box.x + (int)box.width + 8, (int)box.y - 2, 34, textColor);
}

// 绘制按钮
void DrawButton(Rectangle rect, const char *text){
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    Color fill = hovered ? Color{205, 235, 255, 255} : Color{230, 240, 250, 255};

    DrawRectangleRec(rect, fill);
    DrawRectangleLinesEx(rect, 2, BLUE);

    int fontSize = 26;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, (int)(rect.x + (rect.width - textWidth) * 0.5f), (int)(rect.y + (rect.height - fontSize) * 0.5f), fontSize, DARKGRAY);
}

int main(int argc,char **argv){

    int screenWidth = 1600;
    int screenHeight = 900;
    // 基本参数设置
    if (argc >= 3){
        screenWidth = std::stoi(argv[1]);
        screenHeight = std::stoi(argv[2]);
    }

    const int size = 10;
    const int map_x = (screenWidth - 100) / size;
    const int map_y = (screenHeight - 100) / size;
    const int dx = 50;
    const int dy = 50;

    // 起点和终点
    std::pair<int, int> start = {1, 1};
    std::pair<int, int> end = {map_x - 2, map_y - 2};

    // 地图初始化，获取路径
    Map map(map_x, map_y, size);
    map.summonMaze(start,end, map_x * 0.01, map_x * 0.1, map_x / 2);
    auto astar_path = map.astarSreach(start, end);
    auto bfspath = map.bfsSreach(start, end);

    // 拷贝地图数据，准备绘制
    std::vector<std::vector<int>> okpMap = map.getMap();
    int cellSize = map.size;
    
    InitWindow(screenWidth, screenHeight, "raylib demo");
    SetTargetFPS(60);

    // 复选框状态
    bool bfsChecked = true;
    bool astarChecked = true;
    bool closedChecked = false;

    while (!WindowShouldClose()){
        Rectangle bfsCheckBox = {600, 18, 28, 28};
        Rectangle astarCheckBox = {700, 18, 28, 28};
        Rectangle closedCheckBox = {900, 18, 28, 28};
        Rectangle triggerButton = {(float)screenWidth - 220, 12, 190, 42};

        bfsChecked = UpdateCheckbox(bfsCheckBox, bfsChecked);
        astarChecked = UpdateCheckbox(astarCheckBox, astarChecked);
        closedChecked = UpdateCheckbox(closedCheckBox, closedChecked);

        // 触发事件接口：当按钮被点击时，调用回调函数，并传递当前复选框状态
        if (IsButtonClicked(triggerButton)){
            map.summonMaze(start,end, map_x * 0.01, map_x * 0.1, map_x / 2, closedChecked);
            astar_path = map.astarSreach(start, end);
            bfspath = map.bfsSreach(start, end);
            okpMap = map.getMap();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("bfs-BLUE", 50, 10, 40, BLUE);
        DrawText("astar-GREEN", 300, 10, 40, GREEN);

        DrawCheckbox(bfsCheckBox, bfsChecked, "bfs", BLUE);
        DrawCheckbox(astarCheckBox, astarChecked, "astar", GREEN);
        DrawCheckbox(closedCheckBox, closedChecked, "Closed", BLACK);
        DrawButton(triggerButton, "start");

        // 绘制网格地图
        for (int index_y = 0; index_y < map.height; index_y++){
            for (int index_x = 0; index_x < map.width; index_x++){
                int x = dx + index_x * cellSize;
                int y = dy + index_y * cellSize;
                DrawRectangleLines(x, y, cellSize, cellSize, BLACK);
                if (okpMap[index_x][index_y] == 1){
                    DrawRectangle(dx + index_x * cellSize, dy + index_y * cellSize, cellSize, cellSize, BLACK);
                }
            }
        }

        // 绘制路径
        if (astarChecked){
            if (astar_path.empty()){
                DrawText("astar search fail!", 50, 60, 40, RED);
            }else{
                for (auto p : astar_path){
                    DrawRectangle(dx + p.first * cellSize, dy + p.second * cellSize, cellSize, cellSize, GREEN);
                }
            }
        }
        if (bfsChecked){
            if (bfspath.empty()){
                DrawText("bfs search fail!", 50, 120, 40, RED);
            }else{
                for (auto p : bfspath){
                    DrawRectangle(dx + p.first * cellSize, dy + p.second * cellSize, cellSize, cellSize, BLUE);
                }
            }
        }

        // 绘制起点和终点
        DrawRectangle(dx + start.first * cellSize, dy + start.second * cellSize, cellSize, cellSize, ORANGE);
        DrawRectangle(dx + end.first * cellSize, dy + end.second * cellSize, cellSize, cellSize, RED);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
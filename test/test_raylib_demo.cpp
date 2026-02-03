#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib demo");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 预设几个节点的位置（手动布局示例）
        Vector2 root = { 400, 80 };
        Vector2 left = { 260, 200 };
        Vector2 right = { 540, 200 };
        Vector2 leftLeft = { 180, 320 };
        Vector2 leftRight = { 320, 320 };

        // 1) 先画连线（从父节点到子节点）
        DrawLineV(root, left, GRAY);
        DrawLineV(root, right, GRAY);
        DrawLineV(left, leftLeft, GRAY);
        DrawLineV(left, leftRight, GRAY);

        // 2) 再画节点（圆）
        DrawCircleV(root, 24, SKYBLUE);
        DrawCircleV(left, 24, SKYBLUE);
        DrawCircleV(right, 24, SKYBLUE);
        DrawCircleV(leftLeft, 24, SKYBLUE);
        DrawCircleV(leftRight, 24, SKYBLUE);

        // 3) 节点文本（可选）
        DrawText("A", root.x - 6, root.y - 8, 20, DARKGRAY);
        DrawText("B", left.x - 6, left.y - 8, 20, DARKGRAY);
        DrawText("C", right.x - 6, right.y - 8, 20, DARKGRAY);
        DrawText("D", leftLeft.x - 6, leftLeft.y - 8, 20, DARKGRAY);
        DrawText("E", leftRight.x - 6, leftRight.y - 8, 20, DARKGRAY);



        EndDrawing();
    }

    CloseWindow();
    return 0;
}
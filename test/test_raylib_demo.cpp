#include "raylib.h"
#include <algorithm>
#include <cstring>

static void DrawButton(Rectangle rect, const char* text)
{
    // 纯绘制按钮外观：根据鼠标状态切换颜色（未悬停/悬停/按下）
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, rect);
    bool pressed = hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    Color fill = pressed ? Color{ 180, 220, 255, 255 } : (hovered ? Color{ 205, 235, 255, 255 } : Color{ 230, 240, 250, 255 });
    DrawRectangleRec(rect, fill);
    DrawRectangleLinesEx(rect, 2, hovered ? BLUE : GRAY);

    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, (int)(rect.x + (rect.width - textWidth) * 0.5f), (int)(rect.y + (rect.height - fontSize) * 0.5f), fontSize, DARKGRAY);
}

static void DrawInputBox(Rectangle rect, char* buffer, int maxLen, bool active)
{
    // 输入框只负责“画出来”；文本内容由主循环里的键盘输入逻辑维护
    DrawRectangleRec(rect, Color{ 250, 250, 250, 255 });
    DrawRectangleLinesEx(rect, 2, active ? BLUE : GRAY);

    int fontSize = 20;
    DrawText(buffer, (int)rect.x + 10, (int)rect.y + 10, fontSize, DARKGRAY);

    // 激活时显示闪烁光标：用时间片段实现 0.5s 亮 / 0.5s 灭
    if (active && ((GetTime() * 2) - (int)(GetTime() * 2) < 0.5))
    {
        int textWidth = MeasureText(buffer, fontSize);
        DrawLine((int)rect.x + 10 + textWidth + 2, (int)rect.y + 8, (int)rect.x + 10 + textWidth + 2, (int)rect.y + (int)rect.height - 8, BLUE);
    }
}

static float UpdateSlider(Rectangle trackRect, float minValue, float maxValue, float value)
{
    // 滑动条的“更新 + 绘制”合在一起：返回新值，外部保存
    const float handleRadius = 10.0f;
    Vector2 mouse = GetMousePosition();
    bool hoverTrack = CheckCollisionPointRec(mouse, Rectangle{ trackRect.x, trackRect.y - 8, trackRect.width, trackRect.height + 16 });

    // 按住左键且在轨道附近时，用鼠标 x 映射到 [minValue, maxValue]
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && hoverTrack)
    {
        float ratio = (mouse.x - trackRect.x) / trackRect.width;
        ratio = std::clamp(ratio, 0.0f, 1.0f);
        value = minValue + ratio * (maxValue - minValue);
    }

    DrawRectangleRec(trackRect, LIGHTGRAY);

    float currentRatio = (value - minValue) / (maxValue - minValue);
    currentRatio = std::clamp(currentRatio, 0.0f, 1.0f);
    float handleX = trackRect.x + currentRatio * trackRect.width;

    DrawRectangle((int)trackRect.x, (int)trackRect.y, (int)(handleX - trackRect.x), (int)trackRect.height, SKYBLUE);
    DrawCircle((int)handleX, (int)(trackRect.y + trackRect.height / 2), handleRadius, BLUE);

    return value;
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib demo");
    SetTargetFPS(60);

    char inputText[64] = "Hello Raylib";
    int inputLen = (int)std::strlen(inputText);
    bool inputActive = false;
    float sliderValue = 35.0f;

    // 每一帧：先处理输入状态，再统一绘制
    while (!WindowShouldClose())
    {
        // 右侧 UI 展示区的控件布局（固定坐标，和原树结构逻辑解耦）
        Rectangle inputRect = { 560, 80, 210, 44 };
        Rectangle buttonA = { 560, 140, 100, 44 };
        Rectangle buttonB = { 670, 140, 100, 44 };
        Rectangle sliderRect = { 560, 220, 210, 12 };

        // 鼠标点击输入框时激活输入；点击别处会取消激活
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            inputActive = CheckCollisionPointRec(GetMousePosition(), inputRect);
        }

        // 仅在激活时接收字符输入：可打印字符追加、Backspace 删除
        if (inputActive)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= 32 && key <= 125 && inputLen < 63)
                {
                    inputText[inputLen++] = (char)key;
                    inputText[inputLen] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && inputLen > 0)
            {
                inputLen--;
                inputText[inputLen] = '\0';
            }
        }

        // 每帧更新滑动条值（拖动时变化，不拖动时保持）
        sliderValue = UpdateSlider(sliderRect, 0.0f, 100.0f, sliderValue);

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

        DrawRectangle(545, 55, 240, 210, Color{ 245, 248, 252, 255 });
        DrawRectangleLines(545, 55, 240, 210, LIGHTGRAY);
        DrawText("UI Components", 595, 62, 20, DARKGRAY);

        // 下面三类控件仅做“展示”，不与原有树节点逻辑产生交互
        DrawInputBox(inputRect, inputText, 63, inputActive);
        DrawButton(buttonA, "Button A");
        DrawButton(buttonB, "Button B");
        DrawText("Slider", 560, 195, 20, DARKGRAY);
        DrawRectangleLines((int)sliderRect.x, (int)sliderRect.y, (int)sliderRect.width, (int)sliderRect.height, GRAY);
        DrawText(TextFormat("%.0f", sliderValue), 740, 195, 20, DARKGRAY);



        EndDrawing();
    }

    CloseWindow();
    return 0;
}
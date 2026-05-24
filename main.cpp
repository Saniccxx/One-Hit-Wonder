#include <iostream>
#include "raylib.h"

int main() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    const int screenWidth = 2000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "major major major major");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
#ifdef NDEBUG
        DrawText("Release mode", 67, 67, 20, WHITE);
#else
        DrawText("Debug mode", 67, 67, 20, WHITE);
        DrawFPS(10, 10);
#endif
        EndDrawing();
    }
    CloseWindow();

    std::cout << "arch btw\n";
    return 0;
}

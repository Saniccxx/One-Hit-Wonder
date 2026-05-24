#include "renderer.h"
#include <raylib.h>
#include <string>

void Renderer::init_window(const int width, const int height, const char *title) {
    InitWindow(width, height, title);
}

void Renderer::close_window() {
    CloseWindow();
}

bool Renderer::window_should_close() {
    return WindowShouldClose();
}

void Renderer::begin_drawing() {
    BeginDrawing();
}

void Renderer::end_drawing() {
    EndDrawing();
}

void Renderer::clear_background(const Color color) {
    ClearBackground(color);
}

void Renderer::draw_text(const std::string& text, const int x, const int y, const int fontSize, const Color color) {
    DrawText(text.c_str(), x, y, fontSize, color);
}

void Renderer::draw_fps(const int x, const int y) {
    DrawFPS(x, y);
}


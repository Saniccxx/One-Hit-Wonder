#include "renderer.h"
#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>

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

void Renderer::draw_circle(int x, int y, int radius, Color color) {
    DrawCircle(x, y, radius, color);
}

void Renderer::draw_line(int x1, int y1, int x2, int y2, Color color) {
    DrawLine(x1, y1, x2, y2, color);
}

void Renderer::set_target_fps(int fps) {
    SetTargetFPS(fps);
}
std::vector<int> Renderer::controls(int mode) { // indeces 0-7 are respectively: SPACE, F,D,S,A,J,K,L

    std::vector<int> keys={};
    if (mode == 0) {
        IsKeyDown(KEY_SPACE)? keys.emplace_back(1): keys.emplace_back(0);
        IsKeyDown(KEY_F)? keys.emplace_back(1): keys.emplace_back(0);
        IsKeyDown(KEY_D)? keys.emplace_back(1): keys.emplace_back(0);
        IsKeyDown(KEY_S)? keys.emplace_back(1): keys.emplace_back(0);
        IsKeyDown(KEY_A)? keys.emplace_back(1): keys.emplace_back(0);
        IsKeyDown(KEY_J)? keys.emplace_back(1): keys.emplace_back(0);
        IsKeyDown(KEY_K)? keys.emplace_back(1): keys.emplace_back(0);
        IsKeyDown(KEY_L)? keys.emplace_back(1): keys.emplace_back(0);
    }
    return keys;
}

bool Renderer::is_enter_pressed() {
    return IsKeyPressed(KEY_ENTER);
}

double Renderer::get_delta_time() {
    return GetFrameTime();
}

int Renderer::get_monitor_refresh_rate() {
    return GetMonitorRefreshRate(0);
}

void Renderer::DrawImage(const Texture2D& texture, int x, int y, Color tint) {
    if (texture.id == 0) return; //notgut
    DrawTexture(texture, x, y, tint);
}

#include "renderer.h"
#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
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
std::vector<int> Renderer::controls() {


    int w=0;int s=0;int a=0;int d=0;
    if (IsKeyDown(KEY_W)) w=1;
    if (IsKeyDown(KEY_S)) s=1;
    if (IsKeyDown(KEY_A)) a=1;
    if (IsKeyDown(KEY_D)) d=1;
    std::vector<int> keys={w,s,a,d};
    for (int i=0;i<keys.size();i++) {
        std::cout<<keys[i]<<std::endl;
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

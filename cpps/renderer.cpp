#include "../headers/renderer.h"
#include "../headers/config.h"
#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include <array>

RenderTexture2D Renderer::target = {0};
Shader Renderer::bloom = {0};

void Renderer::init_window(const int width, const int height, const char *title) {
    InitWindow(width, height, title);
    target = LoadRenderTexture(width, height);
    bloom = LoadShader(0, "Resources/shaders/bloom.fs");
}

void Renderer::close_window() {
    UnloadShader(bloom);
    UnloadRenderTexture(target);
    CloseWindow();
}

bool Renderer::window_should_close() {
    return WindowShouldClose();
}

void Renderer::begin_drawing() {
    BeginTextureMode(target);
}

void Renderer::end_drawing() {
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    if (config::enableBloom) {
        BeginShaderMode(bloom);
    }
    DrawTextureRec(target.texture,
        Rectangle{ 0, 0, (float)target.texture.width, (float)-target.texture.height },
        Vector2{ 0, 0 },
        WHITE);
    if (config::enableBloom) {
        EndShaderMode();
    }

    EndDrawing();
}

void Renderer::clear_background(const Color color) {
    ClearBackground(color);
}

void Renderer::draw_text(const std::string_view text, const int x, const int y, const int fontSize, const Color color) {
    DrawText(text.data(), x, y, fontSize, color);
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
Vector2 Renderer::get_mouse_pos() {
    Vector2 mousePos = GetMousePosition();
    return mousePos;
}
std::array<int,3> Renderer::get_mouse_clicks()
{
    std::array<int,3> clicks{};

    clicks[0] = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ? 1 : 0;
    clicks[1] = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) ? 1 : 0;
    clicks[2] = IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON) ? 1 : 0;

    return clicks;
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
    DrawTexture(texture, x, y, tint);
}

void Renderer::init_audio_device() { InitAudioDevice(); }
Sound Renderer::load_sound(const char *fileName) { return LoadSound(fileName); }
void Renderer::play_sound(Sound sound) { PlaySound(sound); }
void Renderer::set_sound_volume(Sound sound, float volume) { SetSoundVolume(sound, volume); }
void Renderer::stop_sound(Sound sound) { StopSound(sound); }
float Renderer::get_frame_time() { return GetFrameTime(); }
bool Renderer::is_key_down(int key) { return IsKeyDown(key); }
bool Renderer::is_key_pressed(int key) { return IsKeyPressed(key); }

Texture2D Renderer::load_texture(const char *fileName) { return LoadTexture(fileName); }
void Renderer::unload_texture(Texture2D texture) { UnloadTexture(texture); }
FilePathList Renderer::load_directory_files_ex(const char *basePath, const char *filter, bool scanSubdirs) { return LoadDirectoryFilesEx(basePath, filter, scanSubdirs); }
void Renderer::unload_directory_files(FilePathList files) { UnloadDirectoryFiles(files); }

bool Renderer::check_collision_point_rec(Vector2 point, Rectangle rec) { return CheckCollisionPointRec(point, rec); }
void Renderer::draw_rectangle_rec(Rectangle rec, Color color) { DrawRectangleRec(rec, color); }
int Renderer::measure_text(const char *text, int fontSize) { return MeasureText(text, fontSize); }
void Renderer::begin_mode_2d(Camera2D camera) { BeginMode2D(camera); }
void Renderer::end_mode_2d() { EndMode2D(); }
Vector2 Renderer::get_screen_to_world_2d(Vector2 position, Camera2D camera) { return GetScreenToWorld2D(position, camera); }
void Renderer::draw_circle_lines(int centerX, int centerY, float radius, Color color) { DrawCircleLines(centerX, centerY, radius, color); }
void Renderer::draw_texture_pro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) { DrawTexturePro(texture, source, dest, origin, rotation, tint); }
bool Renderer::is_mouse_button_pressed(int button) { return IsMouseButtonPressed(button); }

std::pair<int, int> Renderer::get_movement() {
    int dx = 0;
    int dy = 0;
    if (IsKeyDown(KEY_D)) dx += 1;
    if (IsKeyDown(KEY_A)) dx -= 1;
    if (IsKeyDown(KEY_S)) dy += 1;
    if (IsKeyDown(KEY_W)) dy -= 1;
    return {dx, dy};
}

void Renderer::draw_rectangle(int x, int y, int width, int height, Color color) {
    DrawRectangle(x, y, width, height, color);
}

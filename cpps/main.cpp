#include "raylib.h"
#include <iostream>
#include "../headers/renderer.h"
#include "../headers/game.h"
#include <iostream>


int main() {
    constexpr int screenWidth = 1800;
    constexpr int screenHeight = 1100;

    Renderer::init_window(screenWidth, screenHeight, "One hit wonder™");

    Game* game = new Game(screenWidth, screenHeight);
    game->init();

    Renderer::init_window(screenWidth, screenHeight, "One hit wonder™");

    InitAudioDevice();      // Initialize audio device

    Sound C = LoadSound("Resources/C.wav");
    Sound D = LoadSound("Resources/D.wav");
    Sound E = LoadSound("Resources/E.wav");
    Sound F = LoadSound("Resources/F.wav");
    Sound G = LoadSound("Resources/G.wav");
    Sound A = LoadSound("Resources/A.wav");
    Sound B = LoadSound("Resources/B.wav");
    Sound C2 = LoadSound("Resources/C2.wav");

    int hz = Renderer::get_monitor_refresh_rate();
    Renderer::set_target_fps(hz);

    while (!Renderer::window_should_close())
    {
        if (IsKeyDown(KEY_H)) PlaySound(C);
        if (IsKeyDown(KEY_J)) PlaySound(D);
        else StopSound(D);
        if (IsKeyDown(KEY_K)) PlaySound(E);
        else StopSound(E);
        if (IsKeyDown(KEY_L)) PlaySound(F);
        else StopSound(F);
        if (IsKeyDown(KEY_B)) PlaySound(G);
        else StopSound(G);
        if (IsKeyDown(KEY_N)) PlaySound(A);
        else StopSound(A);
        if (IsKeyDown(KEY_M)) PlaySound(B);
        else StopSound(B);
        if (IsKeyDown(KEY_COMMA)) PlaySound(C2);
        else StopSound(C2);
        game->tick();
    }
    Renderer::close_window();

    return 0;
}

#include "raylib.h"
#include <iostream>
#include "../headers/renderer.h"
#include "../headers/game.h"
#include "../headers/config.h"


int main() {
    Renderer::init_window(config::screenWidth, config::screenHeight, "One hit wonder™");
    Game* game = new Game(config::screenWidth, config::screenHeight);
    game->init();


    InitAudioDevice();      // Initialize audio device

    Sound C = LoadSound("Resources/C.wav");
    Sound D = LoadSound("Resources/D.wav");
    Sound E = LoadSound("Resources/E.wav");
    Sound F = LoadSound("Resources/F.wav");
    Sound G = LoadSound("Resources/G.wav");
    Sound A = LoadSound("Resources/A.wav");
    Sound B = LoadSound("Resources/B.wav");
    Sound C2 = LoadSound("Resources/C2.wav");
    Sound retry = LoadSound("Resources/retry.wav");

    int hz = Renderer::get_monitor_refresh_rate();
    Renderer::set_target_fps(hz);

    while (!Renderer::window_should_close())
    {
        static bool wasHeld = false;
        bool isHeld = IsKeyDown(KEY_T);
        if (isHeld && !wasHeld) PlaySound(C);
        if (!isHeld && wasHeld) StopSound(C);
        wasHeld = isHeld;
        static bool wasHeld2 = false;
        bool isHeld2 = IsKeyDown(KEY_Y);
        if (isHeld2 && !wasHeld2) PlaySound(D);
        if (!isHeld2 && wasHeld2) StopSound(D);
        wasHeld2 = isHeld2;
        static bool wasHeld3 = false;
        bool isHeld3 = IsKeyDown(KEY_U);
        if (isHeld3 && !wasHeld3) PlaySound(E);
        if (!isHeld3 && wasHeld3) StopSound(E);
        wasHeld3 = isHeld3;
        static bool wasHeld4 = false;
        bool isHeld4 = IsKeyDown(KEY_I);
        if (isHeld4 && !wasHeld4) PlaySound(F);
        if (!isHeld4 && wasHeld4) StopSound(F);
        wasHeld4 = isHeld4;
        static bool wasHeld5 = false;
        bool isHeld5 = IsKeyDown(KEY_O);
        if (isHeld5 && !wasHeld5) PlaySound(G);
        if (!isHeld5 && wasHeld5) StopSound(G);
        wasHeld5 = isHeld5;
        static bool wasHeld6 = false;
        bool isHeld6 = IsKeyDown(KEY_P);
        if (isHeld6 && !wasHeld6) PlaySound(A);
        if (!isHeld6 && wasHeld6) StopSound(A);
        wasHeld6 = isHeld6;
        static bool wasHeld7 = false;
        bool isHeld7 = IsKeyDown(KEY_LEFT_BRACKET);
        if (isHeld7 && !wasHeld7) PlaySound(B);
        if (!isHeld7 && wasHeld7) StopSound(B);
        wasHeld7 = isHeld7;
        static bool wasHeld8 = false;
        bool isHeld8 = IsKeyDown(KEY_RIGHT_BRACKET);
        if (isHeld8 && !wasHeld8) PlaySound(C2);
        if (!isHeld8 && wasHeld8) StopSound(C2);
        wasHeld8 = isHeld8;
        if (IsKeyPressed(KEY_BACKSPACE)) PlaySound(retry);
        game->tick();
    }
    Renderer::close_window();

    return 0;
}

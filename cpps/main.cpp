#include "raylib.h"
#include <iostream>
#include "../headers/renderer.h"
#include "../headers/game.h"
#include "../headers/config.h"

struct PianoKey {
    int key;
    Sound sound;
    bool wasHeld = false;
    bool isFading = false;
    float volume = 1.0f;
};

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
    Sound retry = LoadSound("Resources/retry2.wav");

    PianoKey pianoKeys[] = {
        { KEY_T, C },
        { KEY_Y, D },
        { KEY_U, E },
        { KEY_I, F },
        { KEY_O, G },
        { KEY_P, A },
        { KEY_LEFT_BRACKET, B },
        { KEY_RIGHT_BRACKET, C2 }
    };

    int hz = Renderer::get_monitor_refresh_rate();
    Renderer::set_target_fps(hz);
    
    while (!Renderer::window_should_close())

    {
        float dt = GetFrameTime();

        for (auto& pk : pianoKeys) {
            bool isHeld = IsKeyDown(pk.key);

            if (isHeld && !pk.wasHeld) {
                pk.isFading = false;
                pk.volume = 1.0f;
                SetSoundVolume(pk.sound, pk.volume);

                PlaySound(pk.sound);
            }

            if (!isHeld && pk.wasHeld) {
                pk.isFading = true;
            }

            if (pk.isFading) {
                pk.volume -= 15.0f * dt;
                if (pk.volume <= 0.0f) {
                    pk.volume = 0.0f;
                    pk.isFading = false;
                    StopSound(pk.sound);
                }
                SetSoundVolume(pk.sound, pk.volume);
            }

            pk.wasHeld = isHeld;
        }

        if (IsKeyPressed(KEY_BACKSPACE)) PlaySound(retry);
        game->tick();
    }
    Renderer::close_window();

    return 0;
    
}

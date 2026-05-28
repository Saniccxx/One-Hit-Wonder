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


    Renderer::init_audio_device();      // Initialize audio device

    Sound C = Renderer::load_sound("Resources/C.wav");
    Sound D = Renderer::load_sound("Resources/D.wav");
    Sound E = Renderer::load_sound("Resources/E.wav");
    Sound F = Renderer::load_sound("Resources/F.wav");
    Sound G = Renderer::load_sound("Resources/G.wav");
    Sound A = Renderer::load_sound("Resources/A.wav");
    Sound B = Renderer::load_sound("Resources/B.wav");
    Sound C2 = Renderer::load_sound("Resources/C2.wav");
    Sound retry = Renderer::load_sound("Resources/retry2.wav");

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
        float dt = Renderer::get_frame_time();

        for (auto& pk : pianoKeys) {
            bool isHeld = Renderer::is_key_down(pk.key);

            if (isHeld && !pk.wasHeld) {
                pk.isFading = false;
                pk.volume = 1.0f;
                Renderer::set_sound_volume(pk.sound, pk.volume);

                Renderer::play_sound(pk.sound);
            }

            if (!isHeld && pk.wasHeld) {
                pk.isFading = true;
            }

            if (pk.isFading) {
                pk.volume -= 15.0f * dt;
                if (pk.volume <= 0.0f) {
                    pk.volume = 0.0f;
                    pk.isFading = false;
                    Renderer::stop_sound(pk.sound);
                }
                Renderer::set_sound_volume(pk.sound, pk.volume);
            }

            pk.wasHeld = isHeld;
        }

        if (Renderer::is_key_pressed(KEY_BACKSPACE)) Renderer::play_sound(retry);
        game->tick();
    }
    Renderer::close_window();

    return 0;
    
}

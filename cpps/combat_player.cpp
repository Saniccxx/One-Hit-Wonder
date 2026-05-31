#include "../headers/combat_player.h"
#include "../headers/game.h"
#include "../headers/renderer.h"
#include <iostream>


struct PianoKey {
    int key;
    Sound sound;
    bool wasHeld = false;
    bool isFading = false;
    float volume = 1.0f;
};


CombatPlayer::CombatPlayer(Game& game): game(game) {

    Sound C = Renderer::load_sound("Resources/C.wav");
    Sound D = Renderer::load_sound("Resources/D.wav");
    Sound E = Renderer::load_sound("Resources/E.wav");
    Sound F = Renderer::load_sound("Resources/F.wav");
    Sound G = Renderer::load_sound("Resources/G.wav");
    Sound A = Renderer::load_sound("Resources/A.wav");
    Sound B = Renderer::load_sound("Resources/B.wav");
    Sound C2 = Renderer::load_sound("Resources/C2.wav");
    Sound retry = Renderer::load_sound("Resources/retry2.wav");

    pianoKeys[0] = { KEY_A, C };
    pianoKeys[1] = { KEY_S, D };
    pianoKeys[2] = { KEY_D, E };
    pianoKeys[3] = { KEY_F, F };
    pianoKeys[4] = { KEY_J, G };
    pianoKeys[5] = { KEY_K, A };
    pianoKeys[6] = { KEY_L, B };
    pianoKeys[7] = { KEY_SEMICOLON, C2 };

}

void CombatPlayer::tick(float delta_time) {
    std::cout << "tick tick";
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
            pk.volume -= 15.0f * delta_time;
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

}



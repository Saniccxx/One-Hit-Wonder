#include "combat_player.h"
#include "game.h"
#include "renderer.h"
#include <iostream>


struct PianoKey {
    int key;
    Sound sound;
    bool wasHeld = false;
    bool isFading = false;
    float volume = 1.0f;
};


CombatPlayer::CombatPlayer(Game& game): game(game) {

    C = game.get_sound("C.wav");
    D = game.get_sound("D.wav");
    E = game.get_sound("E.wav");
    F = game.get_sound("F.wav");
    G = game.get_sound("G.wav");
    A = game.get_sound("A.wav");
    B = game.get_sound("B.wav");
    C2 = game.get_sound("C2.wav");
    retry = game.get_sound("retry2.wav");

    pianoKeys[0] = { KEY_S, C };
    pianoKeys[1] = { KEY_D, D };
    pianoKeys[2] = { KEY_F, E };
    pianoKeys[3] = { KEY_G, F };
    pianoKeys[4] = { KEY_H, G };
    pianoKeys[5] = { KEY_J, A };
    pianoKeys[6] = { KEY_K, B };
    pianoKeys[7] = { KEY_L, C2 };

}

void CombatPlayer::tick(float delta_time) {
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



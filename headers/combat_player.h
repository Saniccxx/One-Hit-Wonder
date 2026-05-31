#pragma once
#include "game.h"
#include "renderer.h"

class Game;
class CombatPlayer {

    struct PianoKey {
        int key;
        Sound sound;
        bool wasHeld = false;
        bool isFading = false;
        float volume = 1.0f;
    };

    Sound C{};
    Sound D{};
    Sound E{};
    Sound F{};
    Sound G{};
    Sound A{};
    Sound B{};
    Sound C2{};
    Sound retry{};

    PianoKey pianoKeys[8];

    Game& game;
    public:
    CombatPlayer(Game& game);
    void tick(float delta_time);


};
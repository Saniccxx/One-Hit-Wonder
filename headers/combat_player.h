#pragma once
#include "game.h"
#include "renderer.h"

class Game;
class CombatPlayer {
    Game& game;
    public:
    CombatPlayer(Game& game);
    void tick(float delta_time);

};
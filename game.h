#pragma once
#include "player.h"
class Player;
class Game {
    public:
    Game(int width, int height);
    void tick();
    void init();
    int width = 1920;
    int height = 1080;
    Player* player = nullptr;

};

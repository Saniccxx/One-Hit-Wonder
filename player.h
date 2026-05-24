#pragma once
#include "game.h"
#include "renderer.h"

class Game;
class Player {
    Game& game;
    public:
    float x;
    float y;
    int min_y;
    int max_y;
    float vel_up;
    float target_y;
    int upwards_gravity = 1;
    int direction = 1;
    Player(float x, float y, Game& game);
    void tick(float delta_time);


    private:
    void movement(float delta_time);
};
#pragma once
#include "game.h"
#include "renderer.h"

class Game;
class Player {
    Game& game;
    public:
    float x;
    float y;
    int min_y = 100;
    int max_y = game.height - 100;
    float vel_up;
    float target_y;
    int upwards_gravity = 1;
    int direction = 1;
    Player(float x, float y, Game& game);
    void tick(float delta_time);
    int note = 0;
    float bar_height = (max_y - min_y) / 7;


    private:
    std::vector<int> buttons;
    void movement(float delta_time);
    int get_note();
};
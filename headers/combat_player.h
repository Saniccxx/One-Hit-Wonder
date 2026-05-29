#pragma once
#include "game.h"
#include "renderer.h"

class Game;
class CombatPlayer {
    Game& game;
    public:
    float x;
    float y;
    int min_y = 100;
    int max_y = game.height - 100;
    float vel_up;
    float target_y;
    int base_speed = 0.5;
    float distance_speed_gain = 0.02;
    int direction = 1;
    CombatPlayer(float x, float y, Game& game);
    void tick(float delta_time);
    int note = 0;
    float bar_height = (max_y - min_y) / 7;


    private:
    std::vector<int> buttons;
    void movement(float delta_time);
    int get_note();
};
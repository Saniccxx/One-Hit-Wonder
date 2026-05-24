#pragma once
#include "game.h"

class Game;
class Obstacle {
public:
    int note;
    float x;
    int y;
    int length;
    int height = 50;
    Game& game;
    Obstacle(float x, int note, int length, Game& game);
    void tick(float delta_time);
private:
    void movement(float delta_time);

};
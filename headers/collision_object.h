#pragma once

#include <string>
#include "jeff_the_display.h"
#include "game.h"
#include "renderer.h"

class JeffTheDisplay;
class CollisionObject {
public:
    CollisionObject(int x, int y, int width, int height, JeffTheDisplay& display);
    void tick(double delta_time);
    bool has_collision = true;
    bool collision();

private:
    int x, y, width, height;
    Game& game;
};


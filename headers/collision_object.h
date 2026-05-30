#pragma once

#include <string>
#include "map_display.h"
#include "game.h"
#include "renderer.h"

class MapDisplay;
class CollisionObject {
public:
    CollisionObject(int x, int y, int width, int height, MapDisplay& display);
    void tick(double delta_time);
    bool has_collision = true;
    bool collision(int px, int py, int size);
    std::vector<int> get_parameters() {
        return {x, y, width, height};
    }

private:
    int x, y, width, height;
    MapDisplay& display;
};


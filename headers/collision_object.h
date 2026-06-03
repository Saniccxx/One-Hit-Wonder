#pragma once

#include <string>
#include "renderer.h"

class MapDisplay;
class CollisionObject {
public:
    CollisionObject(int x, int y, int width, int height, int id, Texture2D tilesheet, MapDisplay& display);
    void tick(double delta_time);
    bool has_collision = true;
    int overlapArea(int px, int py, int size);
    bool collision(int px, int py, int size);
    std::vector<int> get_parameters() {
        return {x, y, width, height};
    }

private:
    int x, y, width, height;
    int id = 0;
    Texture2D tilesheet{0};
    MapDisplay& display;
};


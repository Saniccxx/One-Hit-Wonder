#pragma once

#include <string>

class MapObject {
public:
    MapObject(float x, float y, bool has_collision, float radius=0, std::string_view text="");
    void tick(float player_x, float player_y);
    bool has_collision;
    bool collision(float dx, float dy);

private:
    float x;
    float y;
    float radius;
    std::string text;
};


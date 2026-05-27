#pragma once

#include <string>

class MapObject {
public:
    MapObject(float x, float y, float radius, std::string_view text);
    void tick(float player_x, float player_y);

private:
    float x;
    float y;
    float radius;
    std::string text;
};


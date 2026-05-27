#pragma once

#include <string>

class InteractionObject {
public:
    InteractionObject(float x, float y, float radius, std::string_view text);
    void tick(float player_x, float player_y);

private:
    float x;
    float y;
    float radius;
    std::string text;
};


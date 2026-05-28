#pragma once

#include <string>
#include "renderer.h"

class MapObject {
public:
    MapObject(float x, float y, bool has_collision, float radius=0, std::string_view text="", Texture2D tex={0});
    void tick(float player_x, float player_y, double delta_time);
    bool has_collision;
    bool collision(float dx, float dy);

private:
    float x;
    float y;
    float radius;
    std::string text;
    Texture2D texture;
    int current_frame = 0;
    double frame_timer = 0;
};


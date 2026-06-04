#pragma once

#include <string>
#include <memory>
#include "renderer.h"
#include "dialog.h"

class InteractionObject {
public:
    InteractionObject(float x, float y, float radius, std::string_view text, Texture2D tex);

    DialogResult tick(float player_x, float player_y, double delta_time, const Camera2D* camera = nullptr);

    std::vector<int> notes = {
        0,4,3, 2,1,7,4, 3, 2,1,7, 4, 3, 2,3, 1
    };
    std::vector<int> durations = {
        70, 60, 20, 20, 20, 60, 40, 20, 20, 20, 60, 40, 20, 20, 20, 60
    };

    int minimum_score = 100;
private:
    float x;
    float y;
    float radius;
    std::string text;
    Texture2D texture;
    int current_frame = 0;
    double frame_timer = 0;
    std::unique_ptr<Dialog> dialog;
    bool near_player = false;
};


#pragma once

#include <string>
#include <memory>
#include "renderer.h"
#include "dialog.h"

class InteractionObject {
public:
    InteractionObject(float x, float y, float radius=0, std::string_view text="", Texture2D tex={0});

    InteractionObject(float x, float y, bool has_collision, float radius, std::string_view text, Texture2D tex);

    DialogResult tick(float player_x, float player_y, double delta_time, const Camera2D* camera = nullptr);
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
    std::unique_ptr<Dialog> dialog;
    bool near_player = false;
};


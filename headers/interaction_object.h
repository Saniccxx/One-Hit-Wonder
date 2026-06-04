#pragma once

#include <string>
#include <memory>
#include "renderer.h"
#include "dialog.h"
#include "randomizer.h"

enum class PATROLLING_DIRECTION {
    HORIZONTAL,
    VERTICAL
};

class InteractionObject {
public:
    InteractionObject(float x, float y, float radius, std::string_view text, Texture2D tex, std::vector<int> notes, std::vector<int> durations);

    DialogResult tick(float player_x, float player_y, double delta_time, const Camera2D* camera = nullptr);

    std::vector<int> notes = {
        // Mary had a little lamb
        2, 1, 0, 1, 2, 2, 2,
        1, 1, 1,
        2, 4, 4,

        // Little lamb, little lamb
        2, 1, 0, 1, 2, 2, 2, 2,
        1, 1, 2, 1, 0,

        // Its fleece was white as snow
        4, 4, 2, 1, 0, 1, 2,
        4, 4, 4,
        4, 2, 1, 0
    };

    std::vector<int> durations = {
        // Mary had a little lamb
        50, 50, 50, 50, 50, 50, 100,
        50, 50, 100,
        50, 50, 100,

        // Little lamb, little lamb
        50, 50, 50, 50, 50, 50, 50, 50,
        50, 50, 50, 50, 100,

        // Its fleece was white as snow
        50, 50, 50, 50, 50, 50, 50,
        50, 50, 100,
        50, 50, 50, 100
    };

    std::vector<int> get_notes() const { return notes; }
    std::vector<int> get_durations() const { return durations; }
    // std::vector<int> notes = {
    //     0,4,3, 2,1,7,4, 3, 2,1,7, 4, 3, 2,3, 1
    // };
    // std::vector<int> durations = {
    //     70, 60, 20, 20, 20, 60, 40, 20, 20, 20, 60, 40, 20, 20, 20, 60
    // };
    std::vector<int> notes;
    std::vector<int> durations;
    [[nodiscard]] std::vector<int> get_notes() const { return notes; }
    [[nodiscard]] std::vector<int> get_durations() const { return durations; }
    int minimum_score = 100;
private:
    float x;
    float y;
    float radius;
    std::string text;
    Texture2D texture;
    PATROLLING_DIRECTION patrolling_direction = static_cast<PATROLLING_DIRECTION>(randomizer::get_random_int(0, 1));
    int current_frame = 0;
    double frame_timer = 0;
    std::unique_ptr<Dialog> dialog;
    bool near_player = false;
};


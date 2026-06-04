#pragma once

#include <string>
#include <memory>
#include "renderer.h"
#include "dialog.h"
#include "randomizer.h"
#include "map_player.h"

enum class PATROLLING_DIRECTION {
    HORIZONTAL,
    VERTICAL
};
class MapPlayer;
class InteractionObject {
public:
    InteractionObject(float x, float y, float radius, Texture2D tex, std::vector<int> notes, std::vector<int> durations);
    DialogResult tick(MapPlayer* player, double delta_time, const Camera2D* camera = nullptr);

    // std::vector<int> notes = {
    //     0,4,3, 2,1,7,4, 3, 2,1,7, 4, 3, 2,3, 1
    // };
    // std::vector<int> durations = {
    //     70, 60, 20, 20, 20, 60, 40, 20, 20, 20, 60, 40, 20, 20, 20, 60
    // };
    std::vector<int> notes;
    std::vector<int> durations;
    std::string_view text ="";
    [[nodiscard]] std::vector<int> get_notes() const { return notes; }
    [[nodiscard]] std::vector<int> get_durations() const { return durations; }
    int minimum_score = 0;
    bool beaten = false;
    void setTexture(Texture2D texture);
private:
    float x;
    float y;
    float radius;
    Texture2D texture;
    PATROLLING_DIRECTION patrolling_direction = static_cast<PATROLLING_DIRECTION>(randomizer::get_random_int(0, 1));
    int current_frame = 0;
    double frame_timer = 0;
    std::unique_ptr<Dialog> dialog;
    bool near_player = false;
};


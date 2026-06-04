#pragma once
#include <memory>
#include <stack>
#include <vector>
#include "config.h"
#include "renderer.h"
#include "sequence.h"
class Sequence;
class Display;
class InteractionObject;
struct LoadedTex {
    std::string path;
    Texture2D tex;
};

struct LoadedSound {
    std::string path;
    Sound sound;
};

class Game {
    public:
    Game(Config& config);
    ~Game();
    std::unique_ptr<InteractionObject> interaction_object;
    std::vector<std::unique_ptr<InteractionObject>> interaction_objects;
    int level=12;

    void init();
    void tick();
    std::unique_ptr<Sequence> sequence;
    std::vector<std::vector<int>> notes;
    std::vector<std::vector<int>> durations;
    void request_display_change(std::unique_ptr<Display> new_display);
    void revert_display();
    [[nodiscard]] Display* get_display() const;
    [[nodiscard]] double get_delta_time() const;
    [[nodiscard]] Texture2D get_texture(std::string_view name) const;
    [[nodiscard]] Sound get_sound(std::string_view name) const;
    float player_speed = 20.0f*0.01;

    int width;
    int height;
    bool reverting = false;
    Config& config;
    std::unique_ptr<Display> paused_display;

    private:
    std::vector<LoadedTex> images;
    std::vector<LoadedSound> sounds;
    void set_display(std::unique_ptr<Display> new_display);
    double delta_time = 0.0;
    std::unique_ptr<Display> display;
    std::unique_ptr<Display> pending_display;
    std::unique_ptr<Display> backup_display;
};

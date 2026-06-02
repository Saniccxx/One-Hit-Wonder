#pragma once
#include <memory>
#include <vector>
#include "config.h"
#include "renderer.h"
#include "sequence.h"

class Display;

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
    Game(const Config& config);
    ~Game();

    void init();
    void tick();
    std::unique_ptr<Sequence> sequence;

    void request_display_change(std::unique_ptr<Display> new_display);
    [[nodiscard]] Display* get_display() const;
    [[nodiscard]] double get_delta_time() const;
    [[nodiscard]] Texture2D get_texture(std::string_view name) const;
    [[nodiscard]] Sound get_sound(std::string_view name) const;

    int width;
    int height;
    const Config& config;
    std::unique_ptr<Display> paused_display;

    private:
    std::vector<LoadedTex> images;
    std::vector<LoadedSound> sounds;
    void set_display(std::unique_ptr<Display> new_display);
    double delta_time = 0.0;
    std::unique_ptr<Display> display;
    std::unique_ptr<Display> pending_display;
    // Camera removed from Game; map-specific displays will own their own camera
};

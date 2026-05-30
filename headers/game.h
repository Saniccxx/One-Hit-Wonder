#pragma once
#include <memory>
#include <vector>
#include "config.h"
#include "renderer.h"
#include "sequence.h"

class Display;
class GameCamera;

struct LoadedTex {
    std::string path;
    Texture2D tex;
};

class Game {
    public:
    Game(int width = config::screenWidth, int height = config::screenHeight);
    ~Game();

    void init();
    void tick();
    std::unique_ptr<Sequence> sequence;

    void request_display_change(std::unique_ptr<Display> new_display);
    [[nodiscard]] Display* get_display() const;
    [[nodiscard]] GameCamera* get_camera() const;
    [[nodiscard]] double get_delta_time() const;
    [[nodiscard]] Texture2D get_texture(std::string_view name) const;

    int width;
    int height;

    std::unique_ptr<Display> paused_display;

    private:
    std::vector<LoadedTex> images;
    void set_display(std::unique_ptr<Display> new_display);
    double delta_time = 0.0;
    std::unique_ptr<GameCamera> camera;
    std::unique_ptr<Display> display;
    std::unique_ptr<Display> pending_display;
};

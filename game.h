#pragma once
#include <memory>

class Display;
class Game {
    public:
    Game(int width, int height);
    ~Game();

    void init();
    void tick();

    void request_display_change(std::unique_ptr<Display> new_display);
    [[nodiscard]] Display* get_display() const;
    [[nodiscard]] double get_delta_time() const;

    int width = 1920;
    int height = 1080;

    private:
    void set_display(std::unique_ptr<Display> new_display);
    double delta_time = 0.0;
    std::unique_ptr<Display> display;
    std::unique_ptr<Display> pending_display;
};

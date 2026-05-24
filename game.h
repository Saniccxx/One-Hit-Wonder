#pragma once
#include <memory>

class GameDisplay;
class Game {
    public:
    Game(int width, int height);
    ~Game();

    void init();
    void tick();

    void set_display(std::unique_ptr<GameDisplay> new_display);
    [[nodiscard]] GameDisplay* get_display() const;
    [[nodiscard]] double get_delta_time() const;

    int width = 1920;
    int height = 1080;
    Player* player = nullptr;
    GameCamera* camera = nullptr;
    void controls() const;

    private:
    double delta_time = 0.0;
    std::unique_ptr<GameDisplay> display;
};

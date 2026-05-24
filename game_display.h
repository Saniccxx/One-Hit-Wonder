#pragma once

#include <memory>

class Game;
class Player;
class GameCamera;

class GameDisplay {
public:
    explicit GameDisplay(Game& game);
    ~GameDisplay();

    void init();
    void tick();

private:
    Game& game;
    std::unique_ptr<Player> player;
    std::unique_ptr<GameCamera> camera;
};


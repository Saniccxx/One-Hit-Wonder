#pragma once

#include <memory>
#include "display.h"

class Game;
class Player;
class Button;

class GameDisplay : public Display {
public:
    explicit GameDisplay(Game& game);
    ~GameDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Player> player;
    std::unique_ptr<Button> button;
};


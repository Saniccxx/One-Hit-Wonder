#pragma once

#include "display.h"

class Game;
class GameDisplay;

class StartDisplay : public Display {
public:
    explicit StartDisplay(Game& game);
    ~StartDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
};


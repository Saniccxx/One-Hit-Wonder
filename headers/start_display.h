#pragma once

#include "display.h"
#include <memory>

class Game;
class CombatDisplay;
class Button;

class StartDisplay : public Display {
public:
    explicit StartDisplay(Game& game);
    ~StartDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Button> start_button;
    std::unique_ptr<Button> settings_button;
};

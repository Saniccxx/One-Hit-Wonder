#pragma once

#include "display.h"
#include "particles/particle_system.h"
#include <memory>

class Game;
class CombatDisplay;
class Button;

class EndDisplay : public Display {
public:
    explicit EndDisplay(Game& game);
    ~EndDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Button> end_button;
    std::unique_ptr<Button> credits_button;
    std::unique_ptr<Button> quit_button;
};

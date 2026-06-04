#pragma once

#include "display.h"
#include <memory>

class Game;
class Button;

class TutorialDisplay : public Display {
public:
    explicit TutorialDisplay(Game& game);
    ~TutorialDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Button> continue_button;
    std::unique_ptr<Button> back_button;

    int page = 0; // 0 = lore, 1 = controls
    float anim_timer = 0.0f;
    float key_pulse[8] = {};
};

#pragma once

#include "display.h"
#include <memory>

class Game;
class Button;

class SettingsDisplay : public Display {
public:
    explicit SettingsDisplay(Game& game);
    ~SettingsDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Button> back_button;
};


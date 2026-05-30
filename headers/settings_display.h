#pragma once

#include "display.h"
#include <memory>

class Game;
class Button;

enum class SettingsReturn {
    StartMenu,
    PauseMenu
};

class SettingsDisplay : public Display {
public:
    explicit SettingsDisplay(Game& game, SettingsReturn return_target = SettingsReturn::StartMenu);
    ~SettingsDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    SettingsReturn return_target;
    std::unique_ptr<Button> back_button;
};

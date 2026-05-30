#pragma once

#include "display.h"
#include <memory>

class Game;
class Button;

class PauseDisplay : public Display {
public:
    explicit PauseDisplay(Game& game);
    ~PauseDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Button> resume_button;
    std::unique_ptr<Button> settings_button;
    std::unique_ptr<Button> main_menu_button;
};


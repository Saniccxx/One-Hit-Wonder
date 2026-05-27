#pragma once

#include <memory>
#include "display.h"

class Game;
class CombatPlayer;
class Button;

class CombatDisplay : public Display {
public:
    explicit CombatDisplay(Game& game);
    ~CombatDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<CombatPlayer> player;
    std::unique_ptr<Button> button;
};


#pragma once

#include <memory>
#include "display.h"
#include "sequence.h"
#include "interaction_object.h"

class Game;
class CombatPlayer;
class Button;

class CombatDisplay : public Display {
public:
    explicit CombatDisplay(Game& game, InteractionObject& interaction_object);
    ~CombatDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    InteractionObject& interaction_object;
    std::unique_ptr<CombatPlayer> player;
    std::unique_ptr<Button> button;
    std::unique_ptr<Sequence> sequence;

};


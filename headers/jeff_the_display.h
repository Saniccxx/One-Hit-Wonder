#pragma once

#include <memory>
#include "display.h"
#include "interaction_object.h"

class Game;
class Jeff;

class JeffTheDisplay : public Display {
public:
    explicit JeffTheDisplay(Game& game);
    ~JeffTheDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Jeff> player;
    std::unique_ptr<InteractionObject> interact_obj;
};

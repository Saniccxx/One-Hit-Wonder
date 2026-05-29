#pragma once

#include <memory>
#include "display.h"
#include "interaction_object.h"
#include "collision_object.h"

class Game;
class MapPlayer;
class CollisionObject;

class JeffTheDisplay : public Display {
public:
    explicit JeffTheDisplay(Game& game);
    ~JeffTheDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<MapPlayer> player;
    std::unique_ptr<InteractionObject> interact_obj;
    std::unique_ptr<CollisionObject> collision_obj;
};

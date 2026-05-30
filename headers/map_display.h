#pragma once

#include <memory>
#include "display.h"
#include "interaction_object.h"
#include "collision_object.h"
#include "camera.h"

class Game;
class MapPlayer;
class CollisionObject;

class MapDisplay : public Display {
public:
    explicit MapDisplay(Game& game);
    ~MapDisplay() override;

    void init() override;
    void tick() override;

    std::unique_ptr<MapPlayer> player;
    std::unique_ptr<InteractionObject> interact_obj;
    std::unique_ptr<CollisionObject> collision_obj;

private:
    Game& game;
    std::unique_ptr<GameCamera> camera;
};

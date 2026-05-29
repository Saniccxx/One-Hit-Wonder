#pragma once

#include <memory>
#include "display.h"
#include "map_object.h"

class Game;
class MapPlayer;

class JeffTheDisplay : public Display {
public:
    explicit JeffTheDisplay(Game& game);
    ~JeffTheDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<MapPlayer> player;
    std::unique_ptr<MapObject> interact_obj;
};

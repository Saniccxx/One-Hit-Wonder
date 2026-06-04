#pragma once

#include <memory>
#include <iostream>
#include "display.h"
#include <raylib.h>
#include "interaction_object.h"
#include "collision_object.h"
#include "camera.h"
#include "particles/particle_system.h"

class Game;
class MapPlayer;
class CollisionObject;

class MapDisplay : public Display {
#ifdef NDEBUG
    bool debug = false;
#else
    bool debug = true;
#endif
public:
    explicit MapDisplay(Game& game);
    ~MapDisplay() override;

    void init() override;
    void tick() override;
    void saveMapToJson();
    void loadMapFromJson();
    void place_block(int x, int y, int type, std::optional<int> id = std::nullopt, const std::string& file = "decorative_cracks_walls.png");

    std::unique_ptr<MapPlayer> player;
    ParticleSystem particle_system;
    std::unique_ptr<ParticleGenerator> player_particles;
    static constexpr int tile_size = 50;



private:
    std::string mapDataFullPath;
    void resolveMapDataPath();
    struct LightObject {
        Vector3 position_radius{0.0f, 0.0f, 300.0f};
        Color color{WHITE};
    };

    Game& game;
    int current_block = 1;
    void handle_collision(int i, int j);
    static constexpr int width = 2000;
    static constexpr int height = 1500;
    static constexpr int width_in_tiles = width / tile_size;
    static constexpr int height_in_tiles = height / tile_size;
    std::unique_ptr<CollisionObject> coll_objects[height_in_tiles][width_in_tiles]{};
    std::unique_ptr<GameCamera> camera;
    LightObject light;
};

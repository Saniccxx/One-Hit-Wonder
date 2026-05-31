#include "../headers/map_display.h"

#include <format>
#include <iostream>
#include "../headers/camera.h"
#include "../headers/game.h"
#include "../headers/map_player.h"
#include "../headers/renderer.h"

MapDisplay::MapDisplay(Game& game): game(game) {}

MapDisplay::~MapDisplay() = default;

void MapDisplay::init() {
    if (!camera) {
        camera = std::make_unique<GameCamera>(game.width, game.height);
    }
    player = std::make_unique<MapPlayer>(
        500.0f,
        200.0f,
        game.get_texture("front.png"),
        game.get_texture("back.png"),
        game.get_texture("side.png")

    );

    interact_obj = std::make_unique<InteractionObject>(600.0f, 300.0f, false, 100.0f, "GET OUT!!! IM 13 YOU PERVERT",  game.get_texture("Sigma_salto.png"));
    collision_obj = std::make_unique<CollisionObject>(200,200, 200,200, *this);

    player_particles = std::make_unique<ParticleGenerator>(
        &particle_system,
        player->get_x(), player->get_y(),
        0.0f, 0.0f, // vx, vy
        0.0f,       // angle
        20.0f,      // speed
        60.0f,      // lifespan
        4,          // size
        GREEN,      // color
        60.0f       // rate
    );
    particle_system.add_generator(player_particles.get());
}

void MapDisplay::tick() {
    if (camera) camera->begin_mode();
    std::cout << debug;
    if (Renderer::is_mouse_button_pressed(0)) {
        Vector2 mousePos = Renderer::get_mouse_pos();
        mousePos = Renderer::get_screen_to_world_2d(mousePos, camera->get_camera());
        place_block(mousePos.x, mousePos.y, current_block);
    }
    // Renderer::draw_rectangle(0, 0, 1920, 1080, Renderer::white);
    collision_obj->tick(game.get_delta_time());
    bool collided = false;
    if (collision_obj -> has_collision) {
        std::vector<int> pos = player -> get_pos();
        std::vector<int> arch_pos = player -> get_archive();
        if (collision_obj -> collision(pos[0], pos[1], pos[2])) {
            collided = true;
            std::cout << "collision" << game.get_delta_time() << std::endl;
            if (collision_obj -> collision(arch_pos[0], pos[1], arch_pos[2])) { //verical
                if (pos[1] > arch_pos[1]) player->collision_nudge(0, collision_obj -> get_parameters()[1]);
                else player->collision_nudge(1, collision_obj -> get_parameters()[1] + collision_obj -> get_parameters()[3]);
            }
            else if (collision_obj -> collision(pos[0], arch_pos[1], pos[2])) { //horizontal
                if (pos[0] > arch_pos[0]) player->collision_nudge(2, collision_obj -> get_parameters()[0]);
                else player->collision_nudge(3, collision_obj -> get_parameters()[0] + collision_obj -> get_parameters()[2]);
            }
            else player -> rollback_archive();
        }
    }
    if (!collided) player->update_archive();
    if (interact_obj && player) {
        interact_obj->tick(player->get_x(), player->get_y(), game.get_delta_time());
    }

    if (player) {
        player->tick(static_cast<float>(game.get_delta_time()));
        if (camera) camera->set_target({player->get_x(), player->get_y()});

        auto mv = Renderer::get_movement();
        if (mv.first != 0 || mv.second != 0) {
            player_particles->start();
            player_particles->edit(player->get_x() + player->size/2, player->get_y() + player->size/2, 0, 0);
        } else {
            player_particles->stop();
        }
    }

    particle_system.update(static_cast<float>(game.get_delta_time()));

    for (int i = 0; i < height_in_tiles; i++) {
        for (int j = 0; j < width_in_tiles; j++) {
            if (map[i][j] != 0) {
                Renderer::draw_rectangle(j * tile_size, i * tile_size, tile_size, tile_size, Renderer::red);
            }
        }
    }

    if (player) {
        particle_system.draw();
    }

    if (camera) {
        camera->update(static_cast<float>(game.get_delta_time()));
        GameCamera::end_mode();
    }
}

void MapDisplay::place_block(int x, int y, int type) {
    int tile_x = x / tile_size;
    int tile_y = y / tile_size;
    if (tile_x >= 0 && tile_x < width_in_tiles && tile_y >= 0 && tile_y < height_in_tiles) {
        map[tile_y][tile_x] = type;
    }

}

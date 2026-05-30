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
    player = std::make_unique<MapPlayer>(game, 500.0f, 200.0f);
    interact_obj = std::make_unique<InteractionObject>(600.0f, 300.0f, false, 100.0f, "GET OUT!!! IM 13 YOU PERVERT",  game.get_texture("Sigma_salto.png"));
    collision_obj = std::make_unique<CollisionObject>(200,200, 200,200, *this);
}

void MapDisplay::tick() {

    Renderer::draw_rectangle(0, 0, 1920, 1080, Renderer::white);
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
            if (collision_obj -> collision(pos[0], arch_pos[1], pos[2])) { //horizontal
                if (pos[0] > arch_pos[0]) player->collision_nudge(2, collision_obj -> get_parameters()[0]);
                else player->collision_nudge(3, collision_obj -> get_parameters()[0] + collision_obj -> get_parameters()[2]);
            }
        }
    }
    if (!collided) player->upddate_archive();
    if (interact_obj && player) {
        interact_obj->tick(player->get_x(), player->get_y(), game.get_delta_time());
    }

    if (player) {
        player->tick(static_cast<float>(game.get_delta_time()));
        game.get_camera()->set_target({player->get_x(), player->get_y()});
    }
}

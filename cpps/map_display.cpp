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
        if (collision_obj -> collision(player->get_pos())) {
            collided = true;
            player->collision_nudge();
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

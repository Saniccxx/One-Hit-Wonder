#include "../headers/jeff_the_display.h"

#include <format>
#include <iostream>
#include "../headers/camera.h"
#include "../headers/game.h"
#include "../headers/jeff.h"
#include "../headers/renderer.h"

JeffTheDisplay::JeffTheDisplay(Game& game): game(game) {}

JeffTheDisplay::~JeffTheDisplay() = default;

void JeffTheDisplay::init() {
    player = std::make_unique<Jeff>(game, 500.0f, 200.0f);
    interact_obj = std::make_unique<InteractionObject>(600.0f, 300.0f, 100.0f, "GET OUT!!! IM 13 YOU PERVERT");
}

void JeffTheDisplay::tick() {

    Renderer::draw_rectangle(0, 0, 1920, 1080, Renderer::white);

    if (interact_obj && player) {
        interact_obj->tick(player->get_x(), player->get_y());
    }

    if (player) {
        player->tick(static_cast<float>(game.get_delta_time()));
        game.get_camera()->set_target({player->get_x(), player->get_y()});
    }
}

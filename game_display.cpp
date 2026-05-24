#include "game_display.h"

#include <format>
#include <iostream>

#include "camera.h"
#include "game.h"
#include "player.h"
#include "renderer.h"

GameDisplay::GameDisplay(Game& game): game(game) {}

GameDisplay::~GameDisplay() = default;

void GameDisplay::init() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    std::cout << " helllo epstein ";

    player = std::make_unique<Player>(500, 200, game);
    camera = std::make_unique<GameCamera>(game.width, game.height);
}

void GameDisplay::tick() {
    const auto delta_time = game.get_delta_time();
    std::cout << delta_time << '\n';

    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);

#ifdef NDEBUG
    Renderer::draw_text("Release mode", 67, 67, 20, Renderer::white);
#else
    Renderer::draw_text("Debug mode", 67, 67, 20, Renderer::white);
    Renderer::draw_fps(10, 10);

    if (camera) {
        const auto zoom_text = std::format("Camera Zoom: {:.2f}", camera->get_camera().zoom);
        Renderer::draw_text(zoom_text, 67, 100, 20, Renderer::white);
        std::cout << zoom_text << std::endl;
    }
#endif

    if (player) {
        player->tick(static_cast<float>(delta_time));
    }

    Renderer::end_drawing();
}


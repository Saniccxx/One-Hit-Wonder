#include "../headers/game_display.h"

#include <format>
#include <iostream>

#include "../headers/camera.h"
#include "../headers/game.h"
#include "../headers/player.h"
#include "../headers/Button.h"
#include "../headers/jeff_the_display.h"
#include "../headers/renderer.h"

GameDisplay::GameDisplay(Game& game): game(game) {}

GameDisplay::~GameDisplay() = default;

void GameDisplay::init() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    player = std::make_unique<Player>(500, 200, game);
    button = std::make_unique<Button>(50.0f, 150.0f, 220.0f, 60.0f, "Enable Jeff Mode", 24, BLACK, SKYBLUE, LIGHTGRAY, DARKBLUE);
}

void GameDisplay::tick() {
    const auto delta_time = game.get_delta_time();

#ifdef NDEBUG
    Renderer::draw_text("Release mode", 67, 67, 20, Renderer::white);
#else
    Renderer::draw_text("Debug mode", 67, 67, 20, Renderer::white);
    Renderer::draw_fps(10, 10);

    if (const auto* camera = game.get_camera()) {
        const auto zoom_text = std::format("Camera Zoom: {:.2f}", camera->get_camera().zoom);
        Renderer::draw_text(zoom_text, 67, 100, 20, Renderer::white);
    }
#endif

    if (player) {
        player->tick(static_cast<float>(delta_time));
    }

    if (button) {
        if (const auto* camera = game.get_camera()) {
            button->Update(*camera);
        }
        button->Draw();
        if (button->IsClicked()) {
            game.request_display_change(std::make_unique<JeffTheDisplay>(game));
        }
    }
}


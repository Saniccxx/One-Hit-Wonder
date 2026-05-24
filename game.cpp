#include "game.h"
#include <utility>
#include "game_display.h"
#include "renderer.h"

Game::Game(int width, int height): width(width), height(height) {}

Game::~Game() = default;

void Game::set_display(std::unique_ptr<GameDisplay> new_display) {
    display = std::move(new_display);
}

GameDisplay* Game::get_display() const {
    return display.get();
}

double Game::get_delta_time() const {
    return delta_time;
}

void Game::init() {
    if (!display) {
        set_display(std::make_unique<GameDisplay>(*this));
    }

    display->init();
}

void Game::tick() {
    delta_time = Renderer::get_delta_time() * 1000;

    if (display) {
        display->tick();
    }
}

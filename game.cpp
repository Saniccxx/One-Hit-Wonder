#include "game.h"
#include <iostream>
#include "renderer.h"
#include "player.h"

Game::Game(int width, int height): width(width), height(height) {}

void Game::init() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    std::cout << " helllo epstein ";
    player = new Player(500, 200, *this);
}
double delta_time = 0.0f;
void Game::tick() const {
    delta_time = Renderer::get_delta_time() * 1000;
    std::cout << delta_time<<'\n';
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);

#ifdef NDEBUG
    Renderer::draw_text("Release mode", 67, 67, 20, Renderer::white);
#else
    Renderer::draw_text("Debug mode", 67, 67, 20, Renderer::white);
    Renderer::draw_fps(10, 10);
    Renderer::draw_text("Island", 68, 68, 13, Renderer::white);
#endif
    Renderer::end_drawing();

    player->tick(delta_time);
}

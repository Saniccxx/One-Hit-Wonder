#include "game.h"
#include <utility>
#include "game_display.h"
#include "renderer.h"
#include <iostream>

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

double delta_time = 0.0f;

void Game::controls() const {
    std::cout<<"aaa";

}

void Game::tick(){
    delta_time = Renderer::get_delta_time() * 1000;
    std::cout << delta_time<<'\n';
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);
    Game::controls();

    Renderer::draw_text("Release mode", 67, 67, 20, Renderer::white);
    Renderer::draw_text("Debug mode", 67, 67, 20, Renderer::white);
    Renderer::draw_fps(10, 10);

    if (display) {
        display->tick();
    };
};

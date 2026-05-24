#include "game.h"
#include <utility>
#include "display.h"
#include "start_display.h"
#include "game_display.h"
#include "renderer.h"
#include <iostream>

Game::Game(int width, int height): width(width), height(height) {}

Game::~Game() = default;

void Game::set_display(std::unique_ptr<Display> new_display) {
    display = std::move(new_display);
}

void Game::request_display_change(std::unique_ptr<Display> new_display) {
    pending_display = std::move(new_display);
}

Display* Game::get_display() const {
    return display.get();
}

double Game::get_delta_time() const {
    return delta_time;
}

void Game::init() {
    if (!display) {
        set_display(std::make_unique<StartDisplay>(*this));
    }

    display->init();
}

double delta_time = 0.0f;



void Game::tick(){
    if (pending_display) {
        set_display(std::move(pending_display));
        display->init();
    }

    delta_time = Renderer::get_delta_time() * 1000;
    std::cout << delta_time<<'\n';
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);
    Renderer::controls();
    Renderer::draw_fps(10, 10);


    if (display) {
        display->tick();
    }

    Renderer::end_drawing();
};

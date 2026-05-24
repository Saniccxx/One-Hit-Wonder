#pragma once
#include "game.h"
#include <iostream>
#include "renderer.h"
#include "player.h"

Game::Game(int width, int height): width(width), height(height) {}

void Game::init() {
    std::cout << " helllo epstein ";
    player = new Player(500, 200, *this);
}
double delta_time = 0.0f;
void Game::tick() {
    delta_time = Renderer::get_delta_time() * 1000;
    std::cout << delta_time<<'\n';
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);
    player->tick(delta_time);
}

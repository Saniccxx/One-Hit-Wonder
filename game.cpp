#pragma once
#include "game.h"
#include <iostream>

Game::Game(int width, int height): width(width), height(height) {}

void Game::init() {
    std::cout << " helllo epstein ";
}

void Game::tick() {
    std::cout << "runnin";
}

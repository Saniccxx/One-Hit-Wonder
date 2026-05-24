#pragma once
#include "../headers/game.h"
#include "../headers/obstacle.h"

Obstacle::Obstacle(float x, int note, int length, Game& game): x(x), note(note), length(length), game(game) {}

void Obstacle::tick(float delta_time) {
    movement(delta_time);
}

void Obstacle::movement(float delta_time) {
    x -= delta_time;
}

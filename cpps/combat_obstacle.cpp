#include "../headers/game.h"
#include "../headers/combat_obstacle.h"

CombatObstacle::CombatObstacle(float x, int note, int length, Game& game): x(x), note(note), length(length), game(game) {}

void CombatObstacle::tick(float delta_time) {
    movement(delta_time);
}

void CombatObstacle::movement(float delta_time) {
    x -= delta_time;
}

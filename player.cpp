#include "player.h"
#include "game.h"
#include "renderer.h"

Player::Player(float x, float y, Game& game): x(x), y(y), game(game) {}

void Player::tick(float delta_time) {
    Player::movement(delta_time);
    Renderer::draw_fps(x,y);

}

void Player::movement(float delta_time) {
    y += delta_time / 10;

}

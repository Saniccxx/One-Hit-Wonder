#include "player.h"
#include "game.h"
#include "renderer.h"

Player::Player(float x, float y, Game& game): x(x), y(y), game(game) {
    min_y = 100;
    max_y = game.height - 100;
}

void Player::tick(float delta_time) {
    Player::movement(delta_time);
    Renderer::draw_circle(x, y, 20, Renderer::white);
    Renderer::draw_line(500, min_y, 500, max_y, Renderer::white);

}

void Player::movement(float delta_time) {
    y += delta_time / 10 * direction;
    if (y > max_y) y = max_y;
    else if (y < min_y) y = min_y;
    else return;
    direction *= -1;

}

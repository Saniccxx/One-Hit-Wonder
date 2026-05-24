#include "player.h"
#include "game.h"
#include "renderer.h"
#include <iostream>

Player::Player(float x, float y, Game& game): x(x), y(y), game(game) {}

void Player::tick(float delta_time) {
    Player::movement(delta_time);
    Renderer::draw_circle(x, y, 20, Renderer::white);
    Renderer::draw_line(500, min_y, 500, max_y, Renderer::white);
    target_y = (float)min_y + bar_height * (float)get_note();
    std::cout << bar_height*get_note() << std::endl;



}

int Player::get_note() {
    buttons = Renderer::controls(0);
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i] == 0) return i -1;
    }
    return 7;
}

void Player::movement(float delta_time) {


    // y -= vel_up;
    y = target_y;
    if (y > max_y) y = max_y;
    else if (y < min_y) y = min_y;
}

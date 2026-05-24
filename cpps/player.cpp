#include "../headers/player.h"
#include "../headers/game.h"
#include "../headers/renderer.h"
#include <iostream>

Player::Player(float x, float y, Game& game): x(x), y(y), game(game) {}

void Player::tick(float delta_time) {
    Player::movement(delta_time);
    Renderer::draw_circle(x, y, 20, Renderer::white);
    std::cout << y << " | " << note << std::endl;
    Renderer::draw_line(500, min_y, 500, max_y, Renderer::white);
    note = get_note();
    target_y = (float)min_y + bar_height * note;
    std::cout << target_y << std::endl;



}

int Player::get_note() {
    buttons = Renderer::controls(0);
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i] == 0) return i -1;
    }
    return 7;
}

void Player::movement(float delta_time) {


    int dist = y - target_y;
    int base;
    if (dist < 0) base = base_speed;
    else base = -base_speed;
    vel_up = (base + dist*distance_speed_gain) * delta_time;
    y -= vel_up;
    if (y > max_y) y = max_y;
    else if (y < min_y) y = min_y;
}

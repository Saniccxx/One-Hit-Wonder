#include "../headers/Collision_object.h"
#include "../headers/renderer.h"
#include <cmath>
#include "../headers/map_display.h"
#include "../headers/collision_object.h"
#include <iostream>

#include "../headers/map_player.h"

CollisionObject::CollisionObject(int x, int y, int width, int height, MapDisplay& display)
    : x(x), y(y), height(height), width(width), display(display) {}

void CollisionObject::tick(double delta_time) {
    Renderer::draw_rectangle(x,  y, width, height, Renderer::red);

}

bool CollisionObject::collision(std::vector<int> player_pos) {
    int px = player_pos[0];
    int py = player_pos[1];
    int size = player_pos[2];
    int x2 = x + width;
    int y2 = y + height;
    if (px > x2 || px + size<x) return false;
    if (py > y2 || py + size<y) return false;
    return true;
}

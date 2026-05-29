#include "../headers/Collision_object.h"
#include "../headers/renderer.h"
#include <cmath>
#include "../headers/jeff_the_display.h"
#include "../headers/collision_object.h"

CollisionObject::CollisionObject(int x, int y, int width, int height, JeffTheDisplay& display)
    : x(x), y(y), height(height), width(width), game(game) {}

void CollisionObject::tick(double delta_time) {
    Renderer::draw_rectangle(x,  y, width, height, Renderer::red);
    if (has_collision) collision();
}

bool CollisionObject::collision() {
    return false; //dokoncze to pozniej
}

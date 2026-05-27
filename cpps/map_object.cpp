#include "../headers/map_object.h"
#include "../headers/renderer.h"
#include <cmath>

MapObject::MapObject(float x, float y, float radius, std::string_view text)
    : x(x), y(y), radius(radius), text(text) {}

void MapObject::tick(float player_x, float player_y) {
    Renderer::draw_circle(static_cast<int>(x), static_cast<int>(y), 40, Renderer::black);

    float dx = player_x - x;
    float dy = player_y - y;
    float dist = std::hypot(dx, dy);

    if (dist <= radius) {
        Renderer::draw_rectangle(static_cast<int>(x) - 100, static_cast<int>(y) - 120, 670, 60, Renderer::red);
        Renderer::draw_text(text, static_cast<int>(x) - 90, static_cast<int>(y) - 110, 40, Renderer::green);
    }
}


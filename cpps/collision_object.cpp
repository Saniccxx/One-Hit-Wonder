#include "../headers/renderer.h"
#include <cmath>
#include "../headers/map_display.h"
#include "../headers/collision_object.h"
#include <iostream>

#include "../headers/map_player.h"

CollisionObject::CollisionObject(int x, int y, int width, int height, int id, Texture2D tilesheet, MapDisplay& display)
    : x(x), y(y), height(height), width(width), id(id), tilesheet(tilesheet), display(display) {}

void CollisionObject::tick(double delta_time) {
    if (tilesheet.id != 0) {
        const float tileW = 16.0f;
        const float tileH = 16.0f;

        int cols = tilesheet.width / static_cast<int>(tileW);
        int srcX = (id % cols) * static_cast<int>(tileW);
        int srcY = (id / cols) * static_cast<int>(tileH);

        Rectangle source{static_cast<float>(srcX), static_cast<float>(srcY), tileW, tileH};
        Rectangle dest{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)};
        Vector2 origin{0.0f, 0.0f};
        Renderer::draw_texture_pro(tilesheet, source, dest, origin, 0.0f, Renderer::white);
    } else {
        Renderer::draw_rectangle(x,  y, width, height, Renderer::red);
    }

}

bool CollisionObject::collision(int px, int py, int size) {

    int x2 = x + width;
    int y2 = y + height;
    if (px > x2 || px + size<x) return false;
    if (py > y2 || py + size<y) return false;
    return true;
}

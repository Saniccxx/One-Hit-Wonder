#include "../../headers/particles/particle.h"
#include <algorithm>

Particle::Particle(float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color, Texture2D* texture)
    : x(x), y(y), vx(vx), vy(vy), angle(angle), speed(speed), lifespan(lifespan), size(size), color(color), texture(texture) {}

void Particle::apply_force(float fx, float fy) {
    vx += fx;
    vy += fy;
}

void Particle::update(float offset_x, float offset_y, float delta_time) {
    x += (vx * speed + offset_x) * delta_time;
    y += (vy * speed + offset_y) * delta_time;

    if (color.a > 0 && lifespan > 0) {
        float alpha_decrease = (color.a / ((1.0f / 60.0f) * lifespan)) * delta_time;
        int new_alpha = color.a - std::max(1, (int)alpha_decrease);
        color.a = (std::max(0, new_alpha));
        lifespan -= 60.0f * delta_time;
    }
}

void Particle::draw() const {
    if (texture) {
        Rectangle source = { 0, 0, (float)texture->width, (float)texture->height };
        Rectangle dest = { x, y, (float)size * 2, (float)size * 2 };
        Vector2 origin = { (float)size, (float)size };
        DrawTexturePro(*texture, source, dest, origin, angle, color);
    } else {
        Rectangle rec = { x, y, (float)size * 2, (float)size * 2 };
        Vector2 origin = { (float)size, (float)size };
        DrawRectanglePro(rec, origin, angle, color);
    }
}

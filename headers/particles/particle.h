#pragma once
#include <raylib.h>

class Particle {
public:
    float x;
    float y;
    float vx;
    float vy;
    float angle;
    float speed;
    float lifespan;
    int size;
    Color color;

    Particle(float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color);

    void apply_force(float fx, float fy);
    void update(float offset_x, float offset_y, float delta_time);
    void draw() const;
};

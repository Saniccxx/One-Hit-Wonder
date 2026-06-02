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
    Texture2D* texture;

    Particle(float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color, Texture2D* texture = nullptr);

    void apply_force(float fx, float fy);
    void update(float offset_x, float offset_y, float delta_time);
    void draw() const;
};

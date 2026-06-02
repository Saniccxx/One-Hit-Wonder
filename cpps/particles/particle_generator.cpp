#include "../../headers/particles/particle_generator.h"
#include "../../headers/particles/particle_system.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* ps, float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color, float rate, std::optional<float> x_var, std::optional<float> y_var, std::optional<float> vx_var, std::optional<float> vy_var) :
     particle_system(ps), x(x), y(y), vx(vx), vy(vy), angle(angle), speed(speed), lifespan(lifespan), size(size), color(color), rate(rate), x_variance(x_var.value_or(0.0f)), y_variance(y_var.value_or(0.0f)), vx_variance(vx_var.value_or(0.0f)), vy_variance(vy_var.value_or(0.0f)) {}

void ParticleGenerator::start() {
    active = true;
}

void ParticleGenerator::stop() {
    active = false;
}

void ParticleGenerator::update(float delta_time) {
    if (!active) return;
    time_since_last_particle += delta_time;
    while (time_since_last_particle >= 1.0f / rate) {
        Texture2D* tex = nullptr;
        if (!textures.empty()) {
            tex = textures[GetRandomValue(0, static_cast<int>(textures.size()) - 1)];
        }

        float rx = x + (x_variance > 0.0f ? (float)GetRandomValue(-static_cast<int>(x_variance * 100.0f), static_cast<int>(x_variance * 100.0f)) / 100.0f : 0.0f);
        float ry = y + (y_variance > 0.0f ? (float)GetRandomValue(-static_cast<int>(y_variance * 100.0f), static_cast<int>(y_variance * 100.0f)) / 100.0f : 0.0f);
        float rvx = vx + (vx_variance > 0.0f ? (float)GetRandomValue(-static_cast<int>(vx_variance * 100.0f), static_cast<int>(vx_variance * 100.0f)) / 100.0f : 0.0f);
        float rvy = vy + (vy_variance > 0.0f ? (float)GetRandomValue(-static_cast<int>(vy_variance * 100.0f), static_cast<int>(vy_variance * 100.0f)) / 100.0f : 0.0f);

        particle_system->add_particle(rx, ry, rvx, rvy, angle, speed, lifespan, size, color, tex);
        time_since_last_particle -= 1.0f / rate;
    }
}

#ifndef NDEBUG
void ParticleGenerator::draw() const {
    DrawCircleLines(x, y, 10.0f, RED);
    DrawLine(x - 5, y, x + 5, y, RED);
    DrawLine(x, y - 5, x, y + 5, RED);
    DrawRectangleLines(x - x_variance, y - y_variance, x_variance * 2, y_variance * 2, BLACK);
}
#endif

void ParticleGenerator::edit(std::optional<float> ex, std::optional<float> ey,
                             std::optional<float> evx, std::optional<float> evy,
                             std::optional<float> eangle, std::optional<float> espeed,
                             std::optional<float> elifespan, std::optional<int> esize,
                             std::optional<Color> ecolor, std::optional<float> erate,
                             std::optional<float> ex_var, std::optional<float> ey_var,
                             std::optional<float> evx_var, std::optional<float> evy_var) {
    if (ex) x = *ex;
    if (ey) y = *ey;
    if (evx) vx = *evx;
    if (evy) vy = *evy;
    if (eangle) angle = *eangle;
    if (espeed) speed = *espeed;
    if (elifespan) lifespan = *elifespan;
    if (esize) size = *esize;
    if (ecolor) color = *ecolor;
    if (erate) rate = *erate;
    if (ex_var) x_variance = *ex_var;
    if (ey_var) y_variance = *ey_var;
    if (evx_var) vx_variance = *evx_var;
    if (evy_var) vy_variance = *evy_var;
}

#include "../../headers/particles/particle_generator.h"
#include "../../headers/particles/particle_system.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* ps, float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color, float rate)
    : particle_system(ps), x(x), y(y), vx(vx), vy(vy), angle(angle), speed(speed), lifespan(lifespan), size(size), color(color), rate(rate) {}

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
        particle_system->add_particle(x, y, vx, vy, angle, speed, lifespan, size, color);
        time_since_last_particle -= 1.0f / rate;
    }
}

#ifndef NDEBUG
void ParticleGenerator::draw() const {
    DrawCircleLines(x, y, 10.0f, RED);
    DrawLine(x - 5, y, x + 5, y, RED);
    DrawLine(x, y - 5, x, y + 5, RED);
}
#endif

void ParticleGenerator::edit(std::optional<float> ex, std::optional<float> ey,
                             std::optional<float> evx, std::optional<float> evy,
                             std::optional<float> eangle, std::optional<float> espeed,
                             std::optional<float> elifespan, std::optional<int> esize,
                             std::optional<Color> ecolor, std::optional<float> erate) {
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
}

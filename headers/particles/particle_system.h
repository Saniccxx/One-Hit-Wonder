#pragma once

#include <vector>
#include "particle.h"
#include "particle_generator.h"

class ParticleSystem {
public:
    std::vector<Particle> particles;
    std::vector<ParticleGenerator*> generators;

    void add_particle(float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color, Texture2D* texture = nullptr);
    void add_generator(ParticleGenerator* generator);
    void apply_force_to_all(float fx, float fy);
    void update(float delta_time);
    void draw() const;
};

#include "../../headers/particles/particle_system.h"
#include <algorithm>

void ParticleSystem::add_particle(float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color) {
    particles.emplace_back(x, y, vx, vy, angle, speed, lifespan, size, color);
}

void ParticleSystem::add_generator(ParticleGenerator* generator) {
    generators.push_back(generator);
}

void ParticleSystem::apply_force_to_all(float fx, float fy) {
    for (auto& particle : particles) {
        particle.apply_force(fx, fy);
    }
}

void ParticleSystem::update(float delta_time) {
    float dt = delta_time * 0.001f; // to seconds
    float particle_x = 0;
    float particle_y = 0;

    for (auto* generator : generators) {
        generator->update(dt);
    }

    for (auto& particle : particles) {
        particle.update(particle_x, particle_y, dt);
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](const Particle& p) { return p.lifespan <= 0; }), particles.end());
}

void ParticleSystem::draw() const {
    for (const auto& particle : particles) {
        particle.draw();
    }

#ifndef NDEBUG
    for (const auto* generator : generators) {
        generator->draw();
    }
#endif
}

#pragma once
#include <raylib.h>
#include <optional>
#include <vector>

class ParticleSystem;

class ParticleGenerator {
public:
    ParticleSystem* particle_system;
    float x;
    float y;
    float vx;
    float vy;
    float angle;
    float speed;
    float lifespan;
    int size;
    Color color;
    float rate;

    float x_variance = 0.0f;
    float y_variance = 0.0f;
    float vx_variance = 0.0f;
    float vy_variance = 0.0f;

    std::vector<Texture2D> owned_textures;
    std::vector<Texture2D*> textures;

    float time_since_last_particle = 0.0f;
    bool active = false;

    ParticleGenerator(ParticleSystem* ps, float x, float y, float vx, float vy, float angle, float speed, float lifespan, int size, Color color, float rate, std::optional<float> x_var = std::nullopt, std::optional<float> y_var = std::nullopt, std::optional<float> vx_var = std::nullopt, std::optional<float> vy_var = std::nullopt);

    void start();
    void stop();
    void update(float delta_time);
#ifndef NDEBUG
    void draw() const;
#endif

    void edit(std::optional<float> ex = std::nullopt, std::optional<float> ey = std::nullopt,
              std::optional<float> evx = std::nullopt, std::optional<float> evy = std::nullopt,
              std::optional<float> eangle = std::nullopt, std::optional<float> espeed = std::nullopt,
              std::optional<float> elifespan = std::nullopt, std::optional<int> esize = std::nullopt,
              std::optional<Color> ecolor = std::nullopt, std::optional<float> erate = std::nullopt,
              std::optional<float> ex_var = std::nullopt, std::optional<float> ey_var = std::nullopt,
              std::optional<float> evx_var = std::nullopt, std::optional<float> evy_var = std::nullopt);
};

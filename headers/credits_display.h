#pragma once

#include "display.h"
#include "particles/particle_system.h"
#include <memory>

class Game;
class Button;

class CreditsDisplay : public Display {
public:
    explicit CreditsDisplay(Game& game);
    ~CreditsDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    std::unique_ptr<Button> back_button;

    ParticleSystem particle_system;
    std::unique_ptr<ParticleGenerator> note_generator;
};

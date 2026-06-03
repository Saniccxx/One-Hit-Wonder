#pragma once

#include "display.h"
#include "particles/particle_system.h"
#include <memory>
#include <vector>
#include <string>

class Game;
class Button;

enum class SettingsReturn {
    StartMenu,
    PauseMenu
};

struct Resolution {
    int width;
    int height;
    std::string name;
};

class SettingsDisplay : public Display {
public:
    explicit SettingsDisplay(Game& game, SettingsReturn return_target = SettingsReturn::StartMenu);
    ~SettingsDisplay() override;

    void init() override;
    void tick() override;

private:
    Game& game;
    SettingsReturn return_target;
    std::unique_ptr<Button> back_button;
    std::unique_ptr<Button> prev_res_button;
    std::unique_ptr<Button> next_res_button;

    ParticleSystem particle_system;
    std::unique_ptr<ParticleGenerator> note_generator;

    std::vector<Resolution> resolutions;
    int current_res_idx = 0;

    void setup_resolutions();
    void reposition_ui();
};

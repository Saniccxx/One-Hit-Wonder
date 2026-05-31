#include "../headers/combat_display.h"

#include <format>
#include <iostream>

#include "../headers/game.h"
#include "../headers/combat_player.h"
#include "../headers/Button.h"
#include "../headers/map_display.h"
#include "../headers/renderer.h"

CombatDisplay::CombatDisplay(Game& game): game(game) {}

CombatDisplay::~CombatDisplay() = default;

void CombatDisplay::init() {
    player = std::make_unique<CombatPlayer>(game);
    button = std::make_unique<Button>(600.0f, 550.0f, 220.0f/2, 60.0f/2, "Enable Jeff Mode", 24, BLACK, SKYBLUE, LIGHTGRAY, DARKBLUE);
}

void CombatDisplay::tick() {
    const auto delta_time = game.get_delta_time();


    if (player) {
        player->tick(static_cast<float>(delta_time));
    }

    if (button) {
        button->Update(nullptr);
        button->Draw();
        if (button->IsClicked()) {
            game.request_display_change(std::make_unique<MapDisplay>(game));
        }
    }
}


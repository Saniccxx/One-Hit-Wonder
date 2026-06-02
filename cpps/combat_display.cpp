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
    sequence = std::make_unique<Sequence>(game, std::vector<int>{0,1,2,3,4,5,6,7}, std::vector<int>{100,100,200,67,1,100,100,100});
}

void CombatDisplay::tick() {
    const auto delta_time = game.get_delta_time();

    if (sequence) {
        sequence->check();
        sequence->play();
        sequence->draw_progress_bar_chords(100,100,200,30);
        sequence->draw_falling_keys();
    }

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


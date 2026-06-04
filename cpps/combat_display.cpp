#include "../headers/combat_display.h"

#include <format>
#include <iostream>

#include "../headers/game.h"
#include "../headers/combat_player.h"
#include "../headers/Button.h"
#include "../headers/map_display.h"
#include "../headers/interaction_object.h"
#include "../headers/renderer.h"

CombatDisplay::CombatDisplay(Game& game, InteractionObject& interaction_object): game(game), interaction_object(interaction_object) {}

CombatDisplay::~CombatDisplay() = default;

void CombatDisplay::init() {
    player = std::make_unique<CombatPlayer>(game);
    button = std::make_unique<Button>(100.0f, 730.0f, 450.0f, 50.0f, "Return to Map", 24, BLACK, SKYBLUE, LIGHTGRAY, DARKBLUE);

    std::vector<int> notes = {
        0,4,3, 2,1,7,4, 3, 2,1,7, 4, 3, 2,3, 1
    };
    std::vector<int> durations = {
        70, 60, 20, 20, 20, 60, 40, 20, 20, 20, 60, 40, 20, 20, 20, 60
    };
    sequence = std::make_unique<Sequence>(game, notes, durations);
}

void CombatDisplay::tick() {
    const auto delta_time = game.get_delta_time();

    if (sequence) {
        sequence->check();
        sequence->play();
        sequence->draw_progress_bar_chords(100, 100, 450, 40);
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


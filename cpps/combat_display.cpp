#include "combat_display.h"

#include <format>
#include <iostream>

#include "game.h"
#include "combat_player.h"
#include "Button.h"
#include "map_display.h"
#include "interaction_object.h"

CombatDisplay::CombatDisplay(Game& game, InteractionObject* interaction_object): game(game), interaction_object(interaction_object) {}

CombatDisplay::~CombatDisplay() = default;

void CombatDisplay::init() {
    player = std::make_unique<CombatPlayer>(game);
    button = std::make_unique<Button>(100.0f, 730.0f, 450.0f, 50.0f, "Return to Map", 24, BLACK, SKYBLUE, LIGHTGRAY, DARKBLUE);
    sequence = std::make_unique<Sequence>(game, interaction_object);
}

void CombatDisplay::tick() {
    const auto delta_time = game.get_delta_time();

    if (sequence) {
        sequence->check();
        sequence->play();

        sequence->draw_falling_keys();
        sequence->draw_progress_bar_chords(100, 100, 450, 40);
    }

    if (player) {
        player->tick(static_cast<float>(delta_time));
    }

    if (button) {
        button->Update(nullptr);
        button->Draw();
        if (button->IsClicked()) {
            // The setTexture call is now handled in Sequence::progress()
            // if (interaction_object && interaction_object->beaten) {
            //     interaction_object->setTexture(game.get_texture("beaten.png"));
            // }
            game.revert_display();
        }
    }
}
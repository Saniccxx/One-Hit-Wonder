#include "../headers/start_display.h"


#include "../headers/game.h"
#include "../headers/game_display.h"
#include "../headers/renderer.h"

StartDisplay::StartDisplay(Game& game): game(game) {}

StartDisplay::~StartDisplay() = default;

void StartDisplay::init() {}

void StartDisplay::tick() {
    Renderer::draw_text("Press ENTER to Start", 800, 400, 40, Renderer::white);

    if (Renderer::is_enter_pressed()) {
        auto display = std::make_unique<GameDisplay>(game);
        game.request_display_change(std::move(display));
    }
}


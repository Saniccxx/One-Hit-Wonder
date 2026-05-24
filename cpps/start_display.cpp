#include "../headers/start_display.h"


#include "../headers/game.h"
#include "../headers/game_display.h"
#include "../headers/renderer.h"
#include "../headers/Button.h"

StartDisplay::StartDisplay(Game& game): game(game) {}

StartDisplay::~StartDisplay() = default;

void StartDisplay::init() {
    constexpr float button_width = 320.0f;
    constexpr float button_height = 90.0f;
    const float x = (static_cast<float>(game.width) - button_width) / 2.0f;
    const float y = (static_cast<float>(game.height) - button_height) / 2.0f;

    start_button = std::make_unique<Button>(
        x,
        y,
        button_width,
        button_height,
        "Start Game",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );
}

void StartDisplay::tick() {
    Renderer::draw_text("Major Jam", game.width / 2 - 120, game.height / 2 - 120, 50, Renderer::white);

    if (start_button) {
        start_button->Update(*game.get_camera());
        start_button->Draw();
    }

    if (start_button && start_button->IsClicked()) {
        auto display = std::make_unique<GameDisplay>(game);
        game.request_display_change(std::move(display));
    }
}


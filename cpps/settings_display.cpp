#include "../headers/settings_display.h"
#include "../headers/game.h"
#include "../headers/start_display.h"
#include "../headers/pause_display.h"
#include "../headers/renderer.h"
#include "../headers/Button.h"

SettingsDisplay::SettingsDisplay(Game& game, SettingsReturn return_target)
    : game(game), return_target(return_target) {}

SettingsDisplay::~SettingsDisplay() = default;

void SettingsDisplay::init() {
    constexpr float button_width = 320.0f;
    constexpr float button_height = 90.0f;
    const float x = (static_cast<float>(game.width) - button_width) / 2.0f;
    const float y = (static_cast<float>(game.height) - button_height) / 2.0f;

    back_button = std::make_unique<Button>(
        x,
        y,
        button_width,
        button_height,
        "Back",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );
}

void SettingsDisplay::tick() {
    const char* text = "nothing there yet, also i use arch btw";
    int font_size = 50;
    int text_width = Renderer::measure_text(text, font_size);
    Renderer::draw_text(text, game.width / 2 - text_width / 2, game.height / 2 - 120, font_size, Renderer::white);

    if (back_button) {
        back_button->Update(nullptr);
        back_button->Draw();
    }

    if (back_button && back_button->IsClicked()) {
        if (return_target == SettingsReturn::PauseMenu) {
            auto display = std::make_unique<PauseDisplay>(game);
            game.request_display_change(std::move(display));
        } else {
            auto display = std::make_unique<StartDisplay>(game);
            game.request_display_change(std::move(display));
        }
    }
}

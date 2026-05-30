#include "../headers/pause_display.h"

#include "../headers/game.h"
#include "../headers/Button.h"
#include "../headers/renderer.h"
#include "../headers/settings_display.h"
#include "../headers/start_display.h"

PauseDisplay::PauseDisplay(Game& game) : game(game) {}

PauseDisplay::~PauseDisplay() = default;

void PauseDisplay::init() {
    constexpr float button_width = 320.0f;
    constexpr float button_height = 90.0f;
    const float x = (static_cast<float>(game.width) - button_width) / 2.0f;
    const float y = (static_cast<float>(game.height) - button_height) / 2.0f;

    resume_button = std::make_unique<Button>(
        x,
        y - button_height - 20.0f,
        button_width,
        button_height,
        "Resume",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );

    settings_button = std::make_unique<Button>(
        x,
        y,
        button_width,
        button_height,
        "Settings",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );

    main_menu_button = std::make_unique<Button>(
        x,
        y + button_height + 20.0f,
        button_width,
        button_height,
        "Main Menu",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );
}

void PauseDisplay::tick() {
    Renderer::draw_text("Paused", game.width / 2 - 90, game.height / 2 - 200, 50, Renderer::white);

    if (resume_button) {
        resume_button->Update(nullptr);
        resume_button->Draw();
    }

    if (settings_button) {
        settings_button->Update(nullptr);
        settings_button->Draw();
    }

    if (main_menu_button) {
        main_menu_button->Update(nullptr);
        main_menu_button->Draw();
    }

    if (resume_button && resume_button->IsClicked()) {
        if (game.paused_display) {
            game.request_display_change(std::move(game.paused_display));
        }
    }

    if (settings_button && settings_button->IsClicked()) {
        auto display = std::make_unique<SettingsDisplay>(game, SettingsReturn::PauseMenu);
        game.request_display_change(std::move(display));
    }

    if (main_menu_button && main_menu_button->IsClicked()) {
        game.paused_display.reset();
        auto display = std::make_unique<StartDisplay>(game);
        game.request_display_change(std::move(display));
    }
}

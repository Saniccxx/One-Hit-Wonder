#include "../headers/start_display.h"


#include "../headers/game.h"
#include "../headers/map_display.h"
#include "../headers/renderer.h"
#include "../headers/Button.h"
#include "../headers/settings_display.h"
#include "../headers/credits_display.h"

EndDisplay::EndDisplay(Game& game): game(game) {}

EndDisplay::~EndDisplay() = default;

void EndDisplay::init() {
    constexpr float button_width = 300.0f;
    constexpr float button_height = 70.0f;
    const float x = (static_cast<float>(game.width) - button_width) / 2.0f;
    const float y = (static_cast<float>(game.height) - button_height) / 2.0f;

    end_button = std::make_unique<Button>(
        x,
        y - button_height - 20,
        button_width,
        button_height,
        "Return To Main Menu",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );


    credits_button = std::make_unique<Button>(
        x,
        y + button_height + 20,
        button_width,
        button_height,
        "Credits",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );

    quit_button = std::make_unique<Button>(
        x,
        y + (button_height + 20) * 2,
        button_width,
        button_height,
        "Quit",
        36,
        WHITE,
        DARKGRAY,
        GRAY,
        RED
    );


void EndDisplay::tick() {
    DrawRectangleGradientV(0, 0, game.width, game.height, Color{ 15, 12, 36, 255 }, Color{ 5, 4, 12, 255 });

    particle_system.update(static_cast<float>(game.get_delta_time()));
    particle_system.draw();

    const int title_size = 90;
    const int title_width = Renderer::measure_text("Congrats, you WIN", title_size);
    const int title_x = (game.width - title_width) / 2;
    const int title_y = game.height / 2 - 240;

    Renderer::draw_text("Congrats, you WIN", title_x, title_y, title_size, WHITE);

    if (end_button) {
        start_button->Update(nullptr);
        start_button->Draw();
    }

    if (credits_button) {
        credits_button->Update(nullptr);
        credits_button->Draw();
    }

    if (quit_button) {
        quit_button->Update(nullptr);
        quit_button->Draw();
    }

    if (end_button && end_button->IsClicked()) {
        auto display = std::make_unique<MapDisplay>(game);
        game.request_display_change(std::move(display));
    }

    if (credits_button && credits_button->IsClicked()) {
        auto display = std::make_unique<CreditsDisplay>(game);
        game.request_display_change(std::move(display));
    }

    if (quit_button && quit_button->IsClicked()) {
        CloseWindow();
    }
}

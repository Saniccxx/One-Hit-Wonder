#include "start_display.h"


#include "game.h"
#include "map_display.h"
#include "tutorial_display.h"
#include "renderer.h"
#include "Button.h"
#include "settings_display.h"
#include "credits_display.h"

StartDisplay::StartDisplay(Game& game): game(game) {}

StartDisplay::~StartDisplay() = default;

void StartDisplay::init() {
    constexpr float button_width = 300.0f;
    constexpr float button_height = 70.0f;
    const float x = (static_cast<float>(game.width) - button_width) / 2.0f;
    const float y = (static_cast<float>(game.height) - button_height) / 2.0f;

    start_button = std::make_unique<Button>(
        x,
        y - button_height - 20,
        button_width,
        button_height,
        "Start Game",
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

    note_generator = std::make_unique<ParticleGenerator>(
        &particle_system,
        static_cast<float>(game.width) / 2.0f,
        static_cast<float>(game.height) + 50.0f,
        0.0f, -1.2f,
        0.0f,
        50.0f,
        9000.0f,
        12,
        Color{ 255, 255, 255, 180 },
        60.0f,
        static_cast<float>(game.width) / 2.0f,
        20.0f,
        0.4f,
        10.0f
    );
    particle_system.add_generator(note_generator.get());

    for (int i = 1; i <= 6; i++) {
        std::string name = "note_" + std::to_string(i) + ".png";
        Texture2D tex = game.get_texture(name);
        if (tex.id != 0) {
            // Convert note texture pixels to white
            Image img = LoadImageFromTexture(tex);
            Color* pixels = LoadImageColors(img);
            if (pixels != nullptr) {
                for (int p = 0; p < img.width * img.height; p++) {
                    if (pixels[p].a > 0) {
                        pixels[p].r = 255;
                        pixels[p].g = 255;
                        pixels[p].b = 255;
                    }
                }
                UpdateTexture(tex, pixels);
                UnloadImageColors(pixels);
            }
            UnloadImage(img);

            note_generator->owned_textures.push_back(tex);
        }
    }
    for (auto& t : note_generator->owned_textures) {
        note_generator->textures.push_back(&t);
    }
    note_generator->start();
}

void StartDisplay::tick() {
    DrawRectangleGradientV(0, 0, game.width, game.height, Color{ 15, 12, 36, 255 }, Color{ 5, 4, 12, 255 });

    particle_system.update(static_cast<float>(game.get_delta_time()));
    particle_system.draw();

    const int title_size = 90;
    const int title_width = Renderer::measure_text("One Hit Wonder", title_size);
    const int title_x = (game.width - title_width) / 2;
    const int title_y = game.height / 2 - 240;

    Renderer::draw_text("One Hit Wonder", title_x, title_y, title_size, WHITE);

    if (start_button) {
        start_button->Update(nullptr);
        start_button->Draw();
    }

    if (settings_button) {
        settings_button->Update(nullptr);
        settings_button->Draw();
    }

    if (credits_button) {
        credits_button->Update(nullptr);
        credits_button->Draw();
    }

    if (quit_button) {
        quit_button->Update(nullptr);
        quit_button->Draw();
    }

    if (start_button && start_button->IsClicked()) {
        auto display = std::make_unique<TutorialDisplay>(game);
        game.request_display_change(std::move(display));
    }

    if (settings_button && settings_button->IsClicked()) {
        auto display = std::make_unique<SettingsDisplay>(game, SettingsReturn::StartMenu);
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

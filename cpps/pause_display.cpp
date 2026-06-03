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

    quit_button = std::make_unique<Button>(
        x,
        y + (button_height + 20.0f) * 2.0f,
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

void PauseDisplay::tick() {
    DrawRectangleGradientV(0, 0, game.width, game.height, Color{ 15, 12, 36, 255 }, Color{ 5, 4, 12, 255 });
    Renderer::draw_text("Paused", game.width / 2 - 90, game.height / 2 - 200, 50, Renderer::white);

    particle_system.update(static_cast<float>(game.get_delta_time()));
    particle_system.draw();

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

    if (quit_button) {
        quit_button->Update(nullptr);
        quit_button->Draw();
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

    if (quit_button && quit_button->IsClicked()) {
        CloseWindow();
    }
}

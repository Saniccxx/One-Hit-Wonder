#include "settings_display.h"
#include "game.h"
#include "start_display.h"
#include "pause_display.h"
#include "renderer.h"
#include "Button.h"

SettingsDisplay::SettingsDisplay(Game& game, SettingsReturn return_target)
    : game(game), return_target(return_target) {}

SettingsDisplay::~SettingsDisplay() = default;

void SettingsDisplay::setup_resolutions() {
    int monitor = GetCurrentMonitor();
    int mon_w = GetMonitorWidth(monitor);
    int mon_h = GetMonitorHeight(monitor);

    resolutions = {
        { 1280, 720, "1280x720 (16:9)" },
        { 1600, 900, "1600x900 (16:9)" },
        { 1920, 1080, "1920x1080 (16:9)" },
        { 2000, 1020, "2000x1020" },
        { 2560, 1440, "2560x1440 (16:9)" }
    };

    bool already_listed = false;
    for (const auto& r : resolutions) {
        if (r.width == mon_w && r.height == mon_h) {
            already_listed = true;
            break;
        }
    }
    if (!already_listed) {
        resolutions.push_back({ mon_w, mon_h,
            std::to_string(mon_w) + "x" + std::to_string(mon_h) + " (Native)" });
    }

    bool found = false;
    for (size_t i = 0; i < resolutions.size(); i++) {
        if (resolutions[i].width == game.width && resolutions[i].height == game.height) {
            current_res_idx = static_cast<int>(i);
            found = true;
            break;
        }
    }
    if (!found) {
        resolutions.push_back({ game.width, game.height,
            std::to_string(game.width) + "x" + std::to_string(game.height) + " (Current)" });
        current_res_idx = static_cast<int>(resolutions.size() - 1);
    }
}

void SettingsDisplay::reposition_ui() {
    constexpr float button_width = 300.0f;
    constexpr float button_height = 70.0f;
    const float x = (static_cast<float>(game.width) - button_width) / 2.0f;
    const float y = (static_cast<float>(game.height) - button_height) / 2.0f;

    prev_res_button = std::make_unique<Button>(
        x - 230.0f,
        y,
        80.0f,
        button_height,
        "<",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );

    next_res_button = std::make_unique<Button>(
        x + button_width + 150.0f,
        y,
        80.0f,
        button_height,
        ">",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );

    back_button = std::make_unique<Button>(
        x,
        y + button_height + 40.0f,
        button_width,
        button_height,
        "Back",
        36,
        WHITE,
        DARKBLUE,
        BLUE,
        SKYBLUE
    );

    if (note_generator) {
        note_generator->edit(
            static_cast<float>(game.width) / 2.0f,
            static_cast<float>(game.height) + 50.0f,
            std::nullopt, std::nullopt,
            std::nullopt, std::nullopt,
            std::nullopt, std::nullopt,
            std::nullopt, std::nullopt,
            static_cast<float>(game.width) / 2.0f
        );
    }
}

void SettingsDisplay::init() {
    setup_resolutions();

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

    reposition_ui();
}

void SettingsDisplay::tick() {
    DrawRectangleGradientV(0, 0, game.width, game.height, Color{ 15, 12, 36, 255 }, Color{ 5, 4, 12, 255 });

    particle_system.update(static_cast<float>(game.get_delta_time()));
    particle_system.draw();

    const int title_size = 90;
    const int title_width = Renderer::measure_text("Settings", title_size);
    const int title_x = (game.width - title_width) / 2;
    const int title_y = game.height / 2 - 240;

    Renderer::draw_text("Settings", title_x, title_y, title_size, WHITE);

    std::string res_text = "Resolution: " + resolutions[current_res_idx].name;
    const int label_size = 36;
    const int label_width = Renderer::measure_text(res_text.c_str(), label_size);
    constexpr float button_height = 70.0f;
    const float y = (static_cast<float>(game.height) - button_height) / 2.0f;
    const float label_x = (static_cast<float>(game.width) - label_width) / 2.0f;
    const float label_y = y + (button_height - label_size) / 2.0f;
    Renderer::draw_text(res_text, static_cast<int>(label_x), static_cast<int>(label_y), label_size, WHITE);

    if (prev_res_button) {
        prev_res_button->Update(nullptr);
        prev_res_button->Draw();
    }

    if (next_res_button) {
        next_res_button->Update(nullptr);
        next_res_button->Draw();
    }

    if (back_button) {
        back_button->Update(nullptr);
        back_button->Draw();
    }

    if (prev_res_button && prev_res_button->IsClicked()) {
        current_res_idx = (current_res_idx - 1 + resolutions.size()) % resolutions.size();
        int new_w = resolutions[current_res_idx].width;
        int new_h = resolutions[current_res_idx].height;
        SetWindowSize(new_w, new_h);
        game.width = new_w;
        game.height = new_h;
        game.config.set_resolution(new_w, new_h);
        Renderer::resize_target(new_w, new_h);
        reposition_ui();
    }

    if (next_res_button && next_res_button->IsClicked()) {
        current_res_idx = (current_res_idx + 1) % resolutions.size();
        int new_w = resolutions[current_res_idx].width;
        int new_h = resolutions[current_res_idx].height;
        SetWindowSize(new_w, new_h);
        game.width = new_w;
        game.height = new_h;
        game.config.set_resolution(new_w, new_h);
        Renderer::resize_target(new_w, new_h);
        reposition_ui();
    }
    // GDZIEŚ WYWOŁAJ FUNKCJĘ game.config.set_fullscreen(bool fullscreen)
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

#include "credits_display.h"
#include "game.h"
#include "start_display.h"
#include "renderer.h"
#include "Button.h"

CreditsDisplay::CreditsDisplay(Game& game) : game(game) {}

CreditsDisplay::~CreditsDisplay() = default;

void CreditsDisplay::init() {
    constexpr float button_width = 300.0f;
    constexpr float button_height = 70.0f;
    const float x = (static_cast<float>(game.width) - button_width) / 2.0f;
    const float y = static_cast<float>(game.height) - button_height - 60.0f;

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
}

void CreditsDisplay::tick() {
    DrawRectangleGradientV(0, 0, game.width, game.height, Color{ 15, 12, 36, 255 }, Color{ 5, 4, 12, 255 });

    particle_system.update(static_cast<float>(game.get_delta_time()));
    particle_system.draw();

    const int title_size = 90;
    const int title_width = Renderer::measure_text("Credits", title_size);
    const int title_x = (game.width - title_width) / 2;
    const int title_y = game.height / 2 - 290;
    Renderer::draw_text("Credits: ", title_x, title_y, title_size, WHITE);

    struct Participant {
        const char* name;
        const char* role;
    };

    constexpr Participant participants[] = {
        { "rutra8002",    "Display management, GUI, vibe coder"   },
        { "Tobias M",    "architecture and cross-class interactions"},
        { "student",      "Explaining basic programming to brained coworkers"       },
        { "klokleszcz",     "Sequencer sequencing sequence" },
        { "metsej the gathering",   "Never before have I seen more professional ass stealer"          },
    };
    // constexpr Participant participants[] = {
    //     { "Artur + Copillo",    "Professional vibe coder"   },
    //     { "Kummer + Gepetto",    "Semiprofessional vibe coder and level viber"           },
    //     { "Ruter + Klaudia",      "Explaining basic vibing to braindead colleagues from Erasmus+"       },
    //     { "Rutra + Gemi",     "Sequentially vibing sequences" },
    // };

    constexpr int name_size = 36;
    constexpr int role_size = 24;
    constexpr int entry_gap = 72;
    const int block_height = static_cast<int>(sizeof(participants) / sizeof(participants[0])) * entry_gap;
    const int start_y = (game.height - block_height) / 2 - 20;

    for (int i = 0; i < static_cast<int>(sizeof(participants) / sizeof(participants[0])); i++) {
        const int entry_y = start_y + i * entry_gap;

        const int name_w = Renderer::measure_text(participants[i].name, name_size);
        const int name_x = (game.width - name_w) / 2;
        Renderer::draw_text(participants[i].name, name_x, entry_y, name_size, WHITE);

        const int role_w = Renderer::measure_text(participants[i].role, role_size);
        const int role_x = (game.width - role_w) / 2;
        Renderer::draw_text(participants[i].role, role_x, entry_y + name_size + 2, role_size, Color{ 160, 180, 220, 255 });
    }

    if (back_button) {
        back_button->Update(nullptr);
        back_button->Draw();
    }

    if (back_button && back_button->IsClicked()) {
        auto display = std::make_unique<StartDisplay>(game);
        game.request_display_change(std::move(display));
    }
}

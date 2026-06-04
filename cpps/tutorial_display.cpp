#include "tutorial_display.h"
#include "game.h"
#include "renderer.h"
#include "Button.h"
#include "map_display.h"
#include "start_display.h"
#include "raylib.h"
#include <cmath>
#include <string>
#include <array>

TutorialDisplay::TutorialDisplay(Game& game) : game(game) {}
TutorialDisplay::~TutorialDisplay() = default;

void TutorialDisplay::init() {
    constexpr float bw = 260.0f;
    constexpr float bh = 60.0f;
    constexpr float gap = 20.0f;
    const float total_w = bw * 2 + gap;
    const float base_x = (static_cast<float>(game.width) - total_w) / 2.0f;
    const float by = static_cast<float>(game.height) - bh - 50.0f;

    back_button = std::make_unique<Button>(
        base_x, by, bw, bh,
        "Back", 32, WHITE, Color{50,30,30,255}, Color{80,40,40,255}, RED
    );

    continue_button = std::make_unique<Button>(
        base_x + bw + gap, by, bw, bh,
        "Continue", 32, WHITE, DARKBLUE, BLUE, SKYBLUE
    );

    for (int i = 0; i < 8; i++) key_pulse[i] = 0.0f;
    anim_timer = 0.0f;
    page = 0;
}




void TutorialDisplay::tick() {
    anim_timer += GetFrameTime();

    // ── Background ────────────────────────────────────────────────
    DrawRectangleGradientV(0, 0, game.width, game.height,
                           Color{8, 6, 22, 255}, Color{2, 2, 8, 255});

    // Scanline effect (subtle)
    for (int y = 0; y < game.height; y += 4) {
        DrawRectangle(0, y, game.width, 1, Color{0, 0, 0, 30});
    }

    // Animated corner accents
    float pulse = 0.5f + 0.5f * sinf(anim_timer * 2.0f);
    Color accent = Color{
        static_cast<unsigned char>(60 + 40 * pulse),
        static_cast<unsigned char>(80 + 60 * pulse),
        static_cast<unsigned char>(200 + 55 * pulse),
        200
    };
    DrawRectangle(0, 0, game.width, 3, accent);
    DrawRectangle(0, game.height - 3, game.width, 3, accent);

    // ── Page 0: Lore ──────────────────────────────────────────────
    if (page == 0) {
        // Title
        const char* title = "THE MATRIX";
        int tsz = 80;
        int tw = MeasureText(title, tsz);
        float title_glow = 0.5f + 0.5f * sinf(anim_timer * 3.0f);
        // Green tinted glow shadow
        Color green_glow = {0, 255, 80, static_cast<unsigned char>(title_glow * 120)};
        DrawText(title, (game.width - tw) / 2 + 4, 64, tsz, green_glow);
        DrawText(title, (game.width - tw) / 2, 60, tsz, Color{0, 255, 100, 255});


        // Lore text block
        struct LoreLine { const char* text; Color col; int size; };
        LoreLine lines[] = {
            { "You are trapped.",                          Color{200,255,210,255}, 50 },
            { "",                                         WHITE,                   12 },
            { "Locked inside an endless corridor,",       Color{180,220,190,255}, 50 },
            { "deep within the digital prison of the",   Color{180,220,190,255}, 50 },
            { "MATRIX.",                                   Color{0,255,100,255},   50 },
            { "",                                         WHITE,                   12 },
            { "10 guardians stand between you",           Color{180,220,190,255}, 50 },
            { "and freedom.",                              Color{180,220,190,255}, 50 },
            { "",                                         WHITE,                   12 },
            { "Each one must be defeated through",        Color{200,200,220,255}, 50 },
            { "RHYTHM — the language of the Matrix.",     Color{120,180,255,255}, 50 },
            { "",                                         WHITE,                   12 },
            { "Beat all 11 bosses to ESCAPE.",            Color{255,230,80,255},  50 },
        };

        int line_y = 185;
        for (auto& l : lines) {
            if (l.size <= 12) { line_y += l.size; continue; }
            int lw = MeasureText(l.text, l.size);
            DrawText(l.text, (game.width - lw) / 2, line_y, l.size, l.col);
            line_y += l.size + 8;
        }

        // Page indicator dots
        DrawCircle(game.width / 2 - 14, game.height - 130, 6, WHITE);
        DrawCircleLines(game.width / 2 + 14, game.height - 130, 6, Color{120,120,120,200});
    }

    // ── Page 1: Controls ──────────────────────────────────────────
    else {
        const char* title = "CONTROLS";
        int tsz = 72;
        int tw = MeasureText(title, tsz);
        DrawText(title, (game.width - tw) / 2, 55, tsz, GOLD);

        // Subtitle
        const char* sub = "Press the keys as the notes reach the line!";
        int sw = MeasureText(sub, 20);
        DrawText(sub, (game.width - sw) / 2, 160, 20, Color{200,200,160,255});

        // Key row
        const std::array<const char*, 8> labels = {"S","D","F","G","H","J","K","L"};
        const std::array<const char*, 8> notes  = {"Do","Re","Mi","Fa","Sol","La","Si","Do"};
        const std::array<Color, 8> colors = {{
            Color{255, 100, 180, 255},  // S - pink
            Color{150, 80,  255, 255},  // D - purple
            Color{80,  200, 255, 255},  // F - blue
            Color{255, 200, 60,  255},  // G - gold
            Color{255, 200, 60,  255},  // H - gold
            Color{80,  200, 255, 255},  // J - blue
            Color{150, 80,  255, 255},  // K - purple
            Color{255, 100, 180, 255},  // L - pink
        }};

        const int key_w = 90;
        const int key_h = 90;
        const int total_w = 8 * key_w + 7 * 12;
        int start_x = (game.width - total_w) / 2;
        int row_y = 220;

        // Animate a traveling highlight across keys
        float travel = fmodf(anim_timer * 1.2f, 8.0f);
        int active_key = static_cast<int>(travel);
        float sub_pos = travel - active_key;
        float glowing = sinf(sub_pos * 3.14159f);

        for (int i = 0; i < 8; i++) {
            int kx = start_x + i * (key_w + 12);
            bool is_glow = (i == active_key);
            float g = is_glow ? glowing : 0.0f;

            Color base = colors[i];
            Color fill = Color{
                static_cast<unsigned char>(20 + base.r * g * 0.3f),
                static_cast<unsigned char>(20 + base.g * g * 0.3f),
                static_cast<unsigned char>(30 + base.b * g * 0.3f),
                200
            };

            // Key shadow
            DrawRectangleRounded({(float)kx + 4, (float)row_y + 4, (float)key_w, (float)key_h}, 0.2f, 6, Color{0,0,0,120});
            // Key body
            DrawRectangleRounded({(float)kx, (float)row_y, (float)key_w, (float)key_h}, 0.2f, 6, fill);
            // Key border
            Color border = is_glow ? Color{
                base.r, base.g, base.b, static_cast<unsigned char>(180 + 75 * glowing)
            } : Color{80, 80, 110, 180};
            DrawRectangleRoundedLines({(float)kx, (float)row_y, (float)key_w, (float)key_h}, 0.2f, 6, border);

            // Glow halo
            if (is_glow && glowing > 0.1f) {
                DrawRectangleRounded({(float)kx - 4, (float)row_y - 4, (float)key_w + 8, (float)key_h + 8},
                    0.25f, 6, Color{base.r, base.g, base.b, static_cast<unsigned char>(40 * glowing)});
            }

            // Key letter
            int lw = MeasureText(labels[i], 36);
            Color letter_col = is_glow ? Color{base.r, base.g, base.b, 255} : Color{220, 220, 240, 255};
            DrawText(labels[i], kx + key_w/2 - lw/2, row_y + 16, 36, letter_col);

            // Note name below key
            int nw = MeasureText(notes[i], 16);
            DrawText(notes[i], kx + key_w/2 - nw/2, row_y + key_h + 8, 16,
                     Color{base.r, base.g, base.b, 200});
        }

        // Info rows
        struct InfoRow { const char* icon; const char* text; Color col; };
        InfoRow infos[] = {
            { "[BACKSPACE]  ", "Reset the current song if you mess up", Color{200,200,255,255} },
            { "[ESC]  ",       "Pause the game at any time",            Color{200,200,255,255} },
            { "TIP:  ",      "Hit notes on time for PERFECT rating",  Color{255,220,80,255}  },
            { "TIP:  ",      "Build combos for a score multiplier",   Color{255,220,80,255}  },
        };

        int info_y = row_y + key_h + 55;
        for (auto& r : infos) {
            int iw = MeasureText(r.icon, 50);
            DrawText(r.icon, 500, info_y, 50, GOLD);
            DrawText(r.text, 500 + iw, info_y, 50, r.col);
            info_y += 70;
        }

        // Page indicator dots
        DrawCircleLines(game.width / 2 - 14, game.height - 130, 6, Color{120,120,120,200});
        DrawCircle(game.width / 2 + 14, game.height - 130, 6, WHITE);
    }

    // ── Buttons ───────────────────────────────────────────────────
    if (back_button) {
        back_button->Update(nullptr);
        back_button->Draw();
    }
    if (continue_button) {
        continue_button->Update(nullptr);
        continue_button->Draw();
    }

    if (back_button && back_button->IsClicked()) {
        if (page == 1) {
            page = 0;
        } else {
            auto display = std::make_unique<StartDisplay>(game);
            game.request_display_change(std::move(display));
        }
    }

    if (continue_button && continue_button->IsClicked()) {
        if (page == 0) {
            page = 1;
        } else {
            auto display = std::make_unique<MapDisplay>(game);
            game.request_display_change(std::move(display));
        }
    }

    // ── Page hint ────────────────────────────────────────────────
    const char* hint = (page == 0) ? "1 / 2" : "2 / 2";
    int hw = MeasureText(hint, 16);
    DrawText(hint, (game.width - hw)/2, game.height - 130, 16, Color{160,160,180,255});
}

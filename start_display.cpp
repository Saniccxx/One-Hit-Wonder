#include "start_display.h"

#include <Windows.h>
#include "game.h"
#include "game_display.h"
#include "renderer.h"

StartDisplay::StartDisplay(Game& game): game(game) {}

StartDisplay::~StartDisplay() = default;

void StartDisplay::init() {}

void StartDisplay::tick() {
    Renderer::draw_text("Press ENTER to Start", 800, 400, 40, Renderer::white);
    if(GetKeyState('H') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        PlaySound(LoadSound("Resources/C.wav"));
        UnloadSound(LoadSound("Resources/C.wav"));
    }
    if (Renderer::is_enter_pressed()) {
        auto display = std::make_unique<GameDisplay>(game);
        game.request_display_change(std::move(display));
    }
}


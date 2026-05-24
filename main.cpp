#include <iostream>
#include "renderer.h"
#include "game.h"

int main() {
    Game* game = new Game();
    game->init();
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    constexpr int screenWidth = 2000;
    constexpr int screenHeight = 1000;

    Renderer::init_window(screenWidth, screenHeight, "major major major major");

    while (!Renderer::window_should_close())
    {
        game->tick();
        Renderer::begin_drawing();
        Renderer::clear_background(Renderer::black);

#ifdef NDEBUG
        Renderer::draw_text("Release mode", 67, 67, 20, Renderer::white);
#else
        Renderer::draw_text("Debug mode", 67, 67, 20, Renderer::white);
        Renderer::draw_fps(10, 10);
#endif
        Renderer::end_drawing();
    }
    Renderer::close_window();

    std::cout << "arch btw\n";
    return 0;
}

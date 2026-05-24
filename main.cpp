#include <iostream>
#include "renderer.h"
#include "game.h"


int main() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    constexpr int screenWidth = 2000;
    constexpr int screenHeight = 1000;

    Game* game = new Game(screenWidth, screenHeight);
    game->init();

    Renderer::init_window(screenWidth, screenHeight, "major major major major");
    Renderer::set_target_fps(60);

    while (!Renderer::window_should_close())
    {
        game->tick();

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

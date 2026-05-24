#include <iostream>
#include "renderer.h"
#include "game.h"


int main() {
    constexpr int screenWidth = 2000;
    constexpr int screenHeight = 1000;

    Game* game = new Game(screenWidth, screenHeight);
    game->init();

    Renderer::init_window(screenWidth, screenHeight, "major major major major");
    Renderer::set_target_fps(60);

    while (!Renderer::window_should_close())
    {
        game->tick();
    }
    Renderer::close_window();

    std::cout << "arch btw\n";
    return 0;
}

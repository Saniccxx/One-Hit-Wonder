#include <iostream>
#include "renderer.h"
#include "game.h"


int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    Game* game = new Game(screenWidth, screenHeight);
    game->init();

    Renderer::init_window(screenWidth, screenHeight, "One hit wonder™");
    Renderer::set_target_fps(60);

    while (!Renderer::window_should_close())
    {
        game->tick();
    }
    Renderer::close_window();

    std::cout << "arch btw\n";
    return 0;
}

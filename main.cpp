#include <iostream>
#include "renderer.h"
#include "game.h"

int main() {
    constexpr int screenWidth = 960;
    constexpr int screenHeight = 540;

    Game* game = new Game(screenWidth, screenHeight);
    game->init();

    Renderer::init_window(screenWidth, screenHeight, "One hit wonder™");

    int hz = Renderer::get_monitor_refresh_rate();
    Renderer::set_target_fps(hz);

    while (!Renderer::window_should_close())
    {
        game->tick();
    }
    Renderer::close_window();

    std::cout << "arch btw\n";
    return 0;
}

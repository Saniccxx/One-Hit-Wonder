#include <iostream>
#include "../headers/renderer.h"
#include "../headers/game.h"


int main() {
    constexpr int screenWidth = 1800;
    constexpr int screenHeight = 1100;

    Renderer::init_window(screenWidth, screenHeight, "One hit wonder™");

    Game* game = new Game(screenWidth, screenHeight);
    game->init();


    int hz = Renderer::get_monitor_refresh_rate();
    Renderer::set_target_fps(hz);

    while (!Renderer::window_should_close())
    {
        game->tick();
    }
    Renderer::close_window();

    return 0;
}

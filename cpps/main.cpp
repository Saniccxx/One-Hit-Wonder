#include <iostream>
#include "../headers/renderer.h"
#include "../headers/game.h"
#include "../headers/config.h"


int main() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif

    Renderer::init_window(config::screenWidth, config::screenHeight, "One hit wonder™");
    Game game(config::screenWidth, config::screenHeight);
    game.init();
    int hz = Renderer::get_monitor_refresh_rate();
    Renderer::set_target_fps(hz);

    while (!Renderer::window_should_close()){
        game.tick();
    }
    Renderer::close_window();

    return 0;
    
}

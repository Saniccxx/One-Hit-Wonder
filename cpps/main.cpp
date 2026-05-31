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
    const Config config;
    Renderer::init_audio_device();
    Renderer::init_window(config.get_screen_width(), config.get_screen_height(), "One hit wonder™");
    Game game(config);
    game.init();
    int hz = Renderer::get_monitor_refresh_rate();
    Renderer::set_target_fps(hz);

    while (!Renderer::window_should_close()){
        game.tick();
    }
    Renderer::close_window();

    return 0;
    
}

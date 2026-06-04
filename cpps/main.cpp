#include <iostream>
#include "renderer.h"
#include "game.h"
#include "config.h"



int main() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    Config config;
    Renderer::init_audio_device();
    Renderer::init_window(config.get_screen_width(), config.get_screen_height(), "One hit wonder™");
    if (config.get_fullscreen()) {
        Renderer::toggle_fullscreen();
    }
    int text_x = 10;
    int text_y = 10;
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);
    Renderer::end_drawing();
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

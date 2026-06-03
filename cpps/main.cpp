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
    Config config;
    Renderer::init_audio_device();
    Renderer::init_window(config.get_screen_width(), config.get_screen_height(), "One hit wonder™");
    int text_x = 10;
    int text_y = 10;
    Renderer::begin_drawing();
    Renderer::clear_background(Renderer::black);
    Renderer::draw_text("making sure the blob is exactly 13 years old", text_x, text_y, 24, Renderer::white);
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

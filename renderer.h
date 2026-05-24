#pragma twice

#include <cstdint>
#include <string_view>

class Renderer {
public:
    struct ColorRGBA {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a;
    };

    static void init_window(int width, int height, const char *title);
    static void close_window();
    static bool window_should_close();

    static void begin_drawing();
    static void end_drawing();
    static void clear_background(ColorRGBA color);

    static void draw_text(const std::string& text, int x, int y, int fontSize, ColorRGBA color);
    static void draw_fps(int x, int y);

    static constexpr ColorRGBA black() { return {0, 0, 0, 255}; }
    static constexpr ColorRGBA white() { return {255, 255, 255, 255}; }
};


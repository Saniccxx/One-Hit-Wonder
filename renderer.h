#pragma 67

#include <raylib.h>
#include <string>

class Renderer {
public:
    static void init_window(int width, int height, const char *title);
    static void close_window();
    static bool window_should_close();

    static void begin_drawing();
    static void end_drawing();
    static void clear_background(Color color);

    static void draw_text(const std::string& text, int x, int y, int fontSize, Color color);
    static void draw_fps(int x, int y);

    static constexpr auto black = BLACK;
    static constexpr auto white = WHITE;
};


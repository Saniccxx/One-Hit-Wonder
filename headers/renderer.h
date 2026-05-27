#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <utility>
#include <array>

class Renderer {
public:
    static void init_window(int width, int height, const char *title);
    static void close_window();
    static bool window_should_close();

    static void begin_drawing();
    static void end_drawing();
    static void clear_background(Color color);

    static void draw_text(std::string_view text, int x, int y, int fontSize, Color color);
    static void draw_fps(int x, int y);
    static void draw_circle(int x, int y, int radius, Color color);
    static void draw_line(int x1, int y1, int x2, int y2, Color color);
    static std::vector<int> controls(int mode);
    static Vector2  get_mouse_pos();
    static std::array<int,3> get_mouse_clicks();
    static bool is_enter_pressed();

    static std::pair<int,int> get_movement();

    static void draw_rectangle(int x, int y, int width, int height, Color color);

    static void set_target_fps(int fps);
    static double get_delta_time();
    static int get_monitor_refresh_rate();
    static void DrawImage(const Texture2D& texture, int x, int y, Color tint = WHITE);

    static constexpr auto black = BLACK;
    static constexpr auto white = WHITE;
    static constexpr auto red = RED;
    static constexpr auto green = GREEN;
    static constexpr auto blue = BLUE;

private:
    static RenderTexture2D target;
    static Shader bloom;
};

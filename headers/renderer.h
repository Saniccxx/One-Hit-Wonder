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
    static void resize_target(int width, int height);
    static void toggle_fullscreen();

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
    static void draw_rectangle_lines(int x, int y, int width, int height, Color color);

    static void set_target_fps(int fps);
    static double get_delta_time();
    static int get_monitor_refresh_rate();
    static void DrawImage(const Texture2D& texture, int x, int y, Color tint = WHITE);

    static void init_audio_device();
    static Sound load_sound(const char *fileName);
    static void play_sound(Sound sound);
    static void set_sound_volume(Sound sound, float volume);
    static void stop_sound(Sound sound);
    static void unload_sound(Sound sound);
    static float get_frame_time();
    static bool is_key_down(int key);
    static bool is_key_pressed(int key);

    static Font load_font(const char* fileName);
    static Font load_font_ex(const char* fileName, int fontSize, int* fontChars, int glyphCount);
    static Texture2D load_texture(const char* fileName);
    static void unload_texture(Texture2D texture);
    static FilePathList load_directory_files_ex(const char *basePath, const char *filter, bool scanSubdirs);
    static void unload_directory_files(FilePathList files);

    static bool check_collision_point_rec(Vector2 point, Rectangle rec);
    static void draw_rectangle_rec(Rectangle rec, Color color);
    static int measure_text(const char *text, int fontSize);
    static void begin_mode_2d(Camera2D camera);
    static void end_mode_2d();
    static Vector2 get_screen_to_world_2d(Vector2 position, Camera2D camera);
    static void draw_circle_lines(int centerX, int centerY, float radius, Color color);
    static void draw_texture_pro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
    static bool is_mouse_button_clicked(int button);
    static bool is_mouse_button_down(int button);

    static void init_lighting_shader(const char* fragmentShaderPath);
    static void close_lighting_shader();
    static void set_lighting_uniforms(const Vector3* lights, const Vector4* lightColors, int numLights, float ambient);
    static void begin_lighting_mode();
    static void end_lighting_mode();

    static constexpr auto black = BLACK;
    static constexpr auto white = WHITE;
    static constexpr auto red = RED;
    static constexpr auto green = GREEN;
    static constexpr auto blue = BLUE;

private:
    static RenderTexture2D target;
    static Shader bloom;
    static Shader lighting;
    static int lighting_lights_loc;
    static int lighting_light_colors_loc;
    static int lighting_num_lights_loc;
    static int lighting_ambient_loc;
};

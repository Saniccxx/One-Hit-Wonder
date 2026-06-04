#pragma once
#include <nlohmann/json.hpp>

class Config {
    std::string configFullPath;
    int screenWidth;
    int screenHeight;
    bool fullScreen;
    void parseConfig();
    public:
    Config();
    [[nodiscard]] int get_screen_width() const { return screenWidth; }
    [[nodiscard]] int get_screen_height() const { return screenHeight; }
    void set_resolution(int width, int height);
    void set_fullscreen(bool fullScreen);
};


namespace config {
    inline constexpr bool enableBloom = false;
    inline constexpr int defaultScreenWidth = 1280;
    inline constexpr int defaultScreenHeight = 720;
    inline constexpr bool defaultFullScreen = false;
    inline constexpr std::string_view configFileName = "config";
    inline constexpr double animation_frame_delay_ms = 64.0;
}
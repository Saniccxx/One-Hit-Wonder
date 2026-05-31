#pragma once
#include <nlohmann/json.hpp>

class Config {
    int screenWidth;
    int screenHeight;
    void parseConfig();
    public:
    Config();
    [[nodiscard]] int get_screen_width() const { return screenWidth; }
    [[nodiscard]] int get_screen_height() const { return screenHeight; }
};


namespace config {
    inline constexpr bool enableBloom = false;
    inline constexpr int defaultScreenWidth = 1280;
    inline constexpr int defaultScreenHeight = 720;
    inline constexpr std::string_view configFileName = "config";
    inline constexpr std::string_view configFilePath = "../";
    inline constexpr double animation_frame_delay_ms = 64.0;
}
#pragma once
#include <nlohmann/json.hpp>

class Config {
    int screenWidth;
    int screenHeight;
    const std::string file_name;
    void parseConfig();
    public:
    explicit Config(std::string_view file_name);
    [[nodiscard]] int get_screen_width() const { return screenWidth; }
    [[nodiscard]] int get_screen_height() const { return screenHeight; }
};


namespace config {
    inline constexpr bool enableBloom = false;
    inline constexpr int screenWidth = 1000 ;
    inline constexpr int screenHeight = 800;
    inline constexpr double animation_frame_delay_ms = 64.0;
}
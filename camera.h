#pragma once

#include <raylib.h>

class GameCamera {
public:
    GameCamera(int width, int height);

    void begin_mode() const;
    static void end_mode();

    [[nodiscard]] const Camera2D& get_camera() const;

private:
    Camera2D camera{};

    static constexpr float REFERENCE_WIDTH = 1920.0f;
    static constexpr float REFERENCE_HEIGHT = 1080.0f;
};




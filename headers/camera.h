#pragma once

#include <raylib.h>

class GameCamera {
public:
    GameCamera(int width, int height);

    void begin_mode() const;
    static void end_mode();

    void update(float delta_time);
    void set_target(Vector2 new_target);

    [[nodiscard]] const Camera2D& get_camera() const;

private:
    Camera2D camera{};
    Vector2 target_pos{};

    static constexpr float REFERENCE_WIDTH = 1920.0f;
    static constexpr float REFERENCE_HEIGHT = 1080.0f;
};




#include "../headers/camera.h"
#include <algorithm>

GameCamera::GameCamera(const int width, const int height)
{
    const auto width_f = static_cast<float>(width);
    const auto height_f = static_cast<float>(height);
    const float zoom = std::min(width_f / REFERENCE_WIDTH, height_f / REFERENCE_HEIGHT);

    camera.target = {width_f / 2.0f, height_f / 2.0f};
    camera.offset = {width_f / 2.0f, height_f / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = zoom;
}

void GameCamera::begin_mode() const {
    BeginMode2D(camera);
}

void GameCamera::end_mode() {
    EndMode2D();
}

const Camera2D& GameCamera::get_camera() const {
    return camera;
}


#include "../headers/camera.h"
#include <algorithm>

GameCamera::GameCamera(const int width, const int height)
{
    const auto width_f = static_cast<float>(width);
    const auto height_f = static_cast<float>(height);
    const float zoom = std::min(width_f / REFERENCE_WIDTH, height_f / REFERENCE_HEIGHT);

    camera.target = {REFERENCE_WIDTH / 2.0f, REFERENCE_HEIGHT / 2.0f};
    target_pos = camera.target;
    camera.offset = {width_f / 2.0f, height_f / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = zoom;
}

void GameCamera::begin_mode() const {
    Renderer::begin_mode_2d(camera);
}

void GameCamera::end_mode() {
    Renderer::end_mode_2d();
}

void GameCamera::update(float delta_time) {
    float smoothness = 5.0f;
    float dt_sec = delta_time / 1000.0f;
    camera.target.x += (target_pos.x - camera.target.x) * smoothness * dt_sec;
    camera.target.y += (target_pos.y - camera.target.y) * smoothness * dt_sec;
}

void GameCamera::set_target(Vector2 new_target) {
    target_pos = new_target;
}

void GameCamera::reset_to_default() {
    camera.target = {REFERENCE_WIDTH / 2.0f, REFERENCE_HEIGHT / 2.0f};
    target_pos = camera.target;
}

const Camera2D& GameCamera::get_camera() const {
    return camera;
}

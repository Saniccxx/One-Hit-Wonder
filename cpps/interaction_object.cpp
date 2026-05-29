#include "../headers/interaction_object.h"
#include "../headers/renderer.h"
#include <cmath>

InteractionObject::InteractionObject(float x, float y, bool has_collision, float radius, std::string_view text, Texture2D tex)
    : x(x), y(y), has_collision(has_collision), radius(radius), text(text), texture(tex) {}

void InteractionObject::tick(float player_x, float player_y, double delta_time) {
    // animation stuff, magic numbers specific for all my fellas (only one unfortunatelly), maybe fix later ig
    if (texture.id != 0) {
        frame_timer += delta_time;
        if (frame_timer >= 64.0) {
            current_frame++;
            frame_timer = 0;
            if (current_frame >= 16) {
                current_frame = 0;
            }
        }

        Rectangle source = {0, static_cast<float>(current_frame * 64), 64.0f, 64.0f};
        float render_size = (radius > 0) ? radius * 2.0f : 64.0f;
        Rectangle dest = {x, y, render_size, render_size};
        Vector2 origin = {render_size / 2.0f, render_size / 2.0f};

        Renderer::draw_texture_pro(texture, source, dest, origin, 0.0f, Renderer::white);
    } else {
        Renderer::draw_circle(static_cast<int>(x), static_cast<int>(y), 40, Renderer::black);
    }

    float dx = player_x - x;
    float dy = player_y - y;
    float dist = std::hypot(dx, dy);

    if (dist <= radius) {
        Renderer::draw_rectangle(static_cast<int>(x) - 100, static_cast<int>(y) - 120, 670, 60, Renderer::red);
        Renderer::draw_text(text, static_cast<int>(x) - 90, static_cast<int>(y) - 110, 40, Renderer::green);
    }

#ifndef NDEBUG
    Renderer::draw_circle_lines(static_cast<int>(x), static_cast<int>(y), radius, Renderer::red);
#endif
}
    bool has_collision(float dx, float dy) {
    return false; //dokoncze to pozniej
}

#include "interaction_object.h"
#include "renderer.h"
#include "config.h"
#include "map_player.h"

#include <cmath>
#include <iostream>

InteractionObject::InteractionObject(float x, float y, float radius, Texture2D tex, const std::vector<int> notes, const std::vector<int> durations)
    : x(x), y(y), radius(radius), texture(tex), notes(notes), durations(durations)  {
    minimum_score = notes.size() * 200;
    dialog = std::make_unique<Dialog>(text, x, y - 80);
}

void InteractionObject::setTexture(Texture2D texture) {
    this->texture = texture;
    this->current_frame = 0;
    this->frame_timer = 0;
}

DialogResult InteractionObject::tick(MapPlayer* player, double delta_time, const Camera2D* camera) {
    // animation stuff, magic numbers specific for all my fellas (only one unfortunatelly), maybe fix later ig
    if (texture.id != 0) {
        const int frame_size = texture.width;
        const int frame_count = (frame_size > 0) ? (texture.height / frame_size) : 0;

        if (frame_count > 0) {
            frame_timer += delta_time;
            double delay = beaten ? 125.0 : 250;
            if (frame_timer >= delay) {
                frame_timer = 0;
                if (beaten) {
                    if (current_frame < frame_count - 1) {
                        current_frame++;
                    }
                } else {
                    current_frame++;
                    if (current_frame >= frame_count) {
                        current_frame = 0;
                    }
                }
            }

            const auto frame_size_f = static_cast<float>(frame_size);
            Rectangle source = {0.0f, static_cast<float>(current_frame * frame_size), frame_size_f, frame_size_f};
            float render_size = (radius > 0) ? radius * 2.0f : frame_size_f;
            Rectangle dest = {x, y, render_size, render_size};
            Vector2 origin = {render_size / 2.0f, render_size / 2.0f};

            Renderer::draw_texture_pro(texture, source, dest, origin, 0.0f, Renderer::white);
        }
    }

    float dx = player->get_x() - x;
    float dy = player->get_y() - y;
    float dist = std::hypot(dx, dy);

    DialogResult result = DialogResult::None;

    if (dist <= radius and !beaten) {
        if (dialog) {
            player->game->player_speed = 0;
            dialog->Update(camera);
            dialog->Draw();
            result = dialog->GetResult();
            if (result != DialogResult::None)
                dialog ->randomize_text();
        }

    }
    else player->game->player_speed = 20.0f*0.01;


    return result;
}

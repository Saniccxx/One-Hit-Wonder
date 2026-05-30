

#include "../headers/map_player.h"
#include "../headers/renderer.h"
#include "../headers/config.h"

MapPlayer::MapPlayer(float x, float y, Texture2D front_texture, Texture2D back_texture, Texture2D side_texture)
	: x(x), y(y),
	  front_texture(front_texture),
	  back_texture(back_texture),
	  side_texture(side_texture) {

	float archive_x = x;
	float archive_y = y;
}


void MapPlayer::tick(float delta_time) {
	auto mv = Renderer::get_movement();
	int dx = mv.first;
	int dy = mv.second;
	const bool is_moving = (dx != 0 || dy != 0);

	if (dy > 0) {
		facing = Facing::Down;
	} else if (dy < 0) {
		facing = Facing::Up;
	} else if (dx > 0) {
		facing = Facing::Right;
	} else if (dx < 0) {
		facing = Facing::Left;
	}

	x += dx * speed * delta_time;
	y += dy * speed * delta_time;

	const Texture2D* texture = nullptr;
	bool mirror_x = false;

	switch (facing) {
		case Facing::Down:
			texture = &front_texture;
			break;
		case Facing::Up:
			texture = &back_texture;
			break;
		case Facing::Right:
		case Facing::Left:
			texture = &side_texture;
			break;
	}

}

void MapPlayer::update_archive() {
	archive_x = x;
	archive_y = y;
	mirror_x = (facing == Facing::Left);

	if (texture && texture->id != 0) {
		const int frame_size = texture->width;
		const int frame_count = (frame_size > 0) ? (texture->height / frame_size) : 0;

		if (frame_count > 0) {
			if (is_moving) {
				frame_timer += delta_time;
				if (frame_timer >= config::animation_frame_delay_ms) {
					current_frame++;
					frame_timer = 0;
					if (current_frame >= frame_count) {
						current_frame = 0;
					}
				}
			} else {
				frame_timer = 0;
			}

			const auto frame_size_f = static_cast<float>(frame_size);
			Rectangle source = {0.0f, static_cast<float>(current_frame * frame_size), frame_size_f, frame_size_f};
			if (mirror_x) {
				source.x = static_cast<float>(texture->width);
				source.width = -static_cast<float>(texture->width);
			}

			const auto draw_size = static_cast<float>(size);
			Rectangle dest = {x, y, draw_size, draw_size};
			Vector2 origin = {draw_size / 2.0f, draw_size / 2.0f};
			Renderer::draw_texture_pro(*texture, source, dest, origin, 0.0f, Renderer::white);
		}
	}
}

std::vector<int> MapPlayer::get_archive() {
	return {(int)archive_x, (int)archive_y, size};
}
std::vector<int> MapPlayer::get_pos() {
	return {(int)x, (int)y, size};
}

// type 0 is up collision, type 1 is down collision, type 2 is left, type 3 is right
void MapPlayer::collision_nudge(int type, int collided_edge_coord) {
	if (type == 0) y = collided_edge_coord - size;
	if (type == 1) y = collided_edge_coord;
	if (type == 2) x = collided_edge_coord - size;
	if (type == 3) x = collided_edge_coord;
	};


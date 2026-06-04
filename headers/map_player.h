#pragma once
#include <vector>

#include "renderer.h"
class Game;

class MapPlayer {
public:
	float x;
	float y;
	MapPlayer(float x, float y, Texture2D front_texture, Texture2D back_texture, Texture2D side_texture);
	void tick(float delta_time);

	[[nodiscard]] float get_x() const { return x; }
	[[nodiscard]] float get_y() const { return y + static_cast<float>(size) / 4.0f; }

	void update_archive();
	void collision_nudge(int type, int collided_edge_coord);
	float speed = 20.0f*0.01;
	std::array<int, 3> get_archive() const;
	std::array<int, 3> get_pos() const;
	std::array<int, 2> get_tile(int tile_size) const;

	int size = 40;

private:

	enum class Facing {
		Down,
		Up,
		Right,
		Left
	};
	Facing facing = Facing::Down;
	int current_frame = 0;
	double frame_timer = 0;
	Texture2D front_texture{};
	Texture2D back_texture{};
	Texture2D side_texture{};
};



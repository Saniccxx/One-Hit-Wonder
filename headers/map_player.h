#pragma once
#include <vector>

#include "renderer.h"
class Game;

class MapPlayer {
public:
	MapPlayer(float x, float y, Texture2D front_texture, Texture2D back_texture, Texture2D side_texture);
	void tick(float delta_time);

	[[nodiscard]] float get_x() const { return x; }
	[[nodiscard]] float get_y() const { return y + static_cast<float>(size) / 4.0f; }

	void update_archive();
	void collision_nudge(int type, int collided_edge_coord);
	void rollback_archive(){x = archive_x; y = archive_y;};
	std::vector<int> get_archive();
	std::vector<int> get_pos();



private:
	float x;
	float y;
	float archive_x;
	float archive_y;
	int size = 400;
	float speed = 60.0f*0.01;
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



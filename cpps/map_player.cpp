

#include "../headers/map_player.h"
#include "../headers/renderer.h"
#include "../headers/game.h"

MapPlayer::MapPlayer(Game& game, float x, float y): game(game), x(x), y(y) {
	float archive_x = x;
	float archive_y = y;
}

void MapPlayer::tick(float delta_time) {
	auto mv = Renderer::get_movement();
	int dx = mv.first;
	int dy = mv.second;
	Renderer::draw_rectangle(static_cast<int>(x), static_cast<int>(y), size, size, Renderer::black);

	x += dx * speed * delta_time;
	y += dy * speed * delta_time;


}

void MapPlayer::upddate_archive() {
	archive_x = x;
	archive_y = y;
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


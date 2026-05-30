

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

	x += dx * speed * delta_time;
	y += dy * speed * delta_time;


	Renderer::draw_rectangle(static_cast<int>(x), static_cast<int>(y), size, size, Renderer::black);
}

void MapPlayer::upddate_archive() {
	archive_x = x;
	archive_y = y;
}

std::vector<int> MapPlayer::get_archive() {
	return {archive_x, archive_y, size};
}
std::vector<int> MapPlayer::get_pos() {
	return {x, y, size};
}

void MapPlayer::collision_nudge() {
	x = archive_x;
	y = archive_y;
}

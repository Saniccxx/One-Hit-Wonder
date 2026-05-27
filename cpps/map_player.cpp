

#include "../headers/map_player.h"
#include "../headers/renderer.h"
#include "../headers/game.h"

MapPlayer::MapPlayer(Game& game, float x, float y): game(game), x(x), y(y) {}

void MapPlayer::tick(float delta_time) {
	auto mv = Renderer::get_movement();
	int dx = mv.first;
	int dy = mv.second;

	x += dx * speed * delta_time;
	y += dy * speed * delta_time;


	Renderer::draw_rectangle(static_cast<int>(x), static_cast<int>(y), size, size, Renderer::black);
}



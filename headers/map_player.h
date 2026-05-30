#pragma once
#include <vector>

class Game;

class MapPlayer {
public:
	MapPlayer(Game& game, float x, float y);
	void tick(float delta_time);

    [[nodiscard]] float get_x() const { return x + size/2; }
    [[nodiscard]] float get_y() const { return y + size/2; }

	void upddate_archive();
	void collision_nudge();
	std::vector<int> get_archive();
	std::vector<int> get_pos();


private:
	Game& game;
	float x;
	float y;
	float archive_x;
	float archive_y;
	int size = 40;
	float speed = 60.0f*0.01;
};



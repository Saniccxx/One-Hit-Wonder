#pragma once

class Game;

class Jeff {
public:
	Jeff(Game& game, float x, float y);
	void tick(float delta_time);

private:
	Game& game;
	float x;
	float y;
	int size = 40;
	float speed = 240.0f*0.01;
};



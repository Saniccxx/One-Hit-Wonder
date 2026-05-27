#pragma once

class Game;

class Jeff {
public:
	Jeff(Game& game, float x, float y);
	void tick(float delta_time);

    [[nodiscard]] float get_x() const { return x + size/2; }
    [[nodiscard]] float get_y() const { return y + size/2; }

private:
	Game& game;
	float x;
	float y;
	int size = 40;
	float speed = 60.0f*0.01;
};



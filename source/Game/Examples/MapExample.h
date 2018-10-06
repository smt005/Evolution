
#pragma once

#include "Game.h"

class Callback;
class Map;

class MapExample : public Game
{
public:
	~MapExample();

	void init();
	void update(const float dt) override;
	void draw(const float dt) override;

private:
	Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
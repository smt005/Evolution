
#pragma once

#include "Game.h"

class Callback;
class Map;

class MapExample : public Game
{
public:
	~MapExample();

	void init();
	void update();
	void draw();

private:
	Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
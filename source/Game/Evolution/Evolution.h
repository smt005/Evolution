
#pragma once

#include "Game.h"

class Callback;
class Map;

class Evolution : public Game
{
public:
	~Evolution();

	void init();
	void initCallback();
	void update();
	void draw();
	
private:
	Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
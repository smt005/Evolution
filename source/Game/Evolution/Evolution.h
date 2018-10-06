
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
	void update() override;
	void draw() override;
	
private:
	Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
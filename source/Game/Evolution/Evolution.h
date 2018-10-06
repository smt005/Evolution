
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
	void update(const float dt) override;
	void draw(const float dt) override;
	
private:
	Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
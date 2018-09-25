
#pragma once

#include "../../Engine/Game.h"

class Evolution : public Game
{
public:
	Evolution();
	~Evolution();

	void init();
	void update();
	void draw();

private:
	void updateGame();
};
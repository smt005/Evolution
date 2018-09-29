
#pragma once

#include "Game.h"

class Evolution : public Game
{
public:
	Evolution();
	~Evolution();

	void init();
	void update();
	void draw();
};

#pragma once

#include "../../Engine/Game.h"

class Evolution : public Game
{
public:
	Evolution();
	~Evolution();

	void update();

private:
	void updateGame();
};
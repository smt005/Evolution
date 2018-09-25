
#pragma once

class Game
{
public:
	virtual ~Game() {};
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
};
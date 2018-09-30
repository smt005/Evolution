
#pragma once

#include <memory>

class Game
{
public:
	virtual ~Game() {};
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
};

typedef std::shared_ptr<Game> GamePtr;

#pragma once

#include <memory>

class Game
{
public:
	virtual ~Game() {};
	virtual void init() {};
	virtual void update(const float dt) {};
	virtual void draw(const float dt) {};
};

typedef std::shared_ptr<Game> GamePtr;
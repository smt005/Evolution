
#pragma once

#include "Game.h"

namespace Engine { class Callback; }
class Map;

class MapExample : public Engine::Game
{
public:
	~MapExample();

	void init();
	void update() override;
	void draw() override;

private:
	Engine::Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
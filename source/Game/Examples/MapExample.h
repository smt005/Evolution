
#pragma once

#include "Game.h"

namespace Engine { class Callback; }
class Map;

class MapExample : public Engine::Game
{
public:
	~MapExample();

	void init() override;
	void update() override;
	void draw() override;

	void initCallback();
	bool load();
	void save();

private:
	Engine::Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
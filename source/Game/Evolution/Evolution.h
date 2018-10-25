
#pragma once

#include "Game.h"
#include <string>

namespace Engine { class Callback; }
class Map;

class Evolution final : public Engine::Game
{
public:
	~Evolution();
	std::string getName() override { return "Evolution"; }

	void init() override;
	void update() override;
	void draw() override;

	void initCallback();

private:
	Engine::Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};

#pragma once

#include "Game.h"
namespace Engine { class Callback; }
class Map;

class Evolution : public Engine::Game
{
public:
	~Evolution();

	void init();
	void initCallback();
	void update() override;
	void draw() override;
	
private:
	Engine::Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
};
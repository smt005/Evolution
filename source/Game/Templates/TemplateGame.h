#pragma once

#include "Game.h"
#include <string>

namespace Engine { class Callback; }
class Map;
class Greed;

class TemplateGame : public Engine::Game
{
public:
	TemplateGame();
	virtual ~TemplateGame();

	virtual std::string getSaveFileName();
	virtual std::string getMapFileName();

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;

protected:
	virtual void initCallback();
	virtual bool load();
	virtual void save();

protected:
	Engine::Callback* _callback = nullptr;
	Map* _mapGame = nullptr;
	Greed* _greed = nullptr;
};

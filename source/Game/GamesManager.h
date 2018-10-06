#pragma once

#include <string>
#include <memory>

#include "Evolution/Evolution.h"
#include "Examples/MapExample.h"

namespace game
{

Engine::GamePtr getGame(const std::string& name) {
	Engine::Game* game = nullptr;

	if (name == "Evolution") {
		game = new Evolution();
	} else if (name == "MapExample") {
		game = new MapExample();
	}
	else {
		game = new Engine::Game();
	}

	Engine::GamePtr gamePtr(game);
	return gamePtr;
}

};	// game
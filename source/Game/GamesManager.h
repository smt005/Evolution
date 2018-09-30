#pragma once

#include <string>
#include <memory>

#include "Evolution/Evolution.h"
#include "Examples/MapExample.h"

namespace game
{

GamePtr getGame(const std::string& name) {
	Game* game = nullptr;

	if (name == "Evolution") {
		game = new Evolution();
	} else if (name == "MapExample") {
		game = new MapExample();
	}
	else {
		game = new Game();
	}

	GamePtr gamePtr(game);
	return gamePtr;
}

};	// game
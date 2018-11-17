#pragma once

#include <string>
#include <memory>

#include "Evolution/Evolution.h"
#include "Examples/MapExample.h"
#include "CollisionBall/CollisionBall.h"
#include "CollisionBall/MoveToTarget.h"
#include "CollisionBall/MoveToTargetClass.h"
#include "Microbe_02/MicrobeGame_02.h"
#include "Neurons/NeuronsGame.h"

namespace game
{

Engine::GamePtr getGame(const std::string& name) {
	Engine::Game* game = nullptr;

	if (name == "Evolution") {
		game = new Evolution();
	}
	else if (name == "MapExample") {
		game = new MapExample();
	}
	else if (name == "CollisionBall") {
		game = new CollisionBall();
	}
	else if (name == "MoveToTarget") {
		game = new MoveToTarget();
	}
	else if (name == "MoveToTargetClass") {
		game = new MoveToTargetClass();
	}
	else if (name == "MicrobeGame_02") {
		game = new MicrobeGame_02();
	}
	else if (name == "NeuronsGame") {
		game = new NeuronsGame();
	}
	else {
		game = new Engine::DefaultGame();
	}

	Engine::GamePtr gamePtr(game);
	return gamePtr;
}

};	// game
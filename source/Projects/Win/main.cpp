
#include "Core.h"
#include "GamesManager.h"

int main(int argc, char **argv) {
	Engine::GamePtr gamePtr;
	gamePtr = game::getGame(argc > 1 ? argv[1] : "NeuronsGame");	// MapExample Evolution CollisionBall MoveToTarget MoveToTargetClass MicrobeGame_02 NeuronsGame
	return Engine::Core::execution(gamePtr);
}


#include "Core.h"
#include "GamesManager.h"

int main(int argc, char **argv) {
	Engine::GamePtr gamePtr;
	gamePtr = game::getGame(argc > 1 ? argv[1] : "MicrobeGame_02");	// MapExample Evolution CollisionBall MoveToTarget MoveToTargetClass MicrobeGame_02
	return Engine::Core::execution(gamePtr);
}

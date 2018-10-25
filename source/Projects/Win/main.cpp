
#include "Core.h"
#include "GamesManager.h"

int main(int argc, char **argv) {
	Engine::GamePtr gamePtr;
	gamePtr = game::getGame(argc > 1 ? argv[1] : "CollisionBall");	// MapExample Evolution CollisionBall
	return Engine::Core::execution(gamePtr);
}

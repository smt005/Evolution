
#include "Engine.h"
#include "GamesManager.h"

int main(int argc, char **argv) {
	GamePtr gamePtr;
	gamePtr = game::getGame(argc > 1 ? argv[1] : "Evolution");
	return Core::Engine::execution(gamePtr);
}

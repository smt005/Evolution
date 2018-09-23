
#include "../../Engine.h"
#include "../../Game.h"
#include "../../Window.h"

using namespace Core;

Game* Engine::_game = nullptr;
Window* Engine::_window = nullptr;

int Engine::execution(Game* game)
{
	if (!game) return -1;

	_game = game;
	Window window;

	return 0;
}

void Engine::exit()
{

}

void Engine::update()
{
	if (!_game) return;

	_game->update();
}

void Engine::log(const std::string& text)
{
#ifdef DEBUG
	_CrtDbgReport(_CRT_WARN, NULL, 0, NULL, "LOG: %s\n", text.c_str());
#endif // DEBUG
}
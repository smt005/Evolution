
#include "../../Engine.h"
#include "../../Game.h"
#include "../../Window.h"

using namespace Core;

Game* Engine::_game = nullptr;

int Engine::execution(Game* game)
{
	if (!game) return -1;

	_game = game;
	Window::create();

	return 0;
}

void Engine::exit()
{

}

void Engine::init()
{
	if (!_game) return;

	_game->init();
}

void Engine::update()
{
	if (!_game) return;

	_game->update();
}

void Engine::draw()
{
	if (!_game) return;

	_game->draw();
}

void Engine::log(const std::string& text)
{
#ifdef _DEBUG
	_CrtDbgReport(_CRT_WARN, NULL, 0, NULL, "LOG: %s\n", text.c_str());
#endif // DEBUG
}
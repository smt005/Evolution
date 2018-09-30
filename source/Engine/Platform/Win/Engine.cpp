
#include "Engine.h"
#include "Game.h"
#include "Window.h"
#include "Common/Help.h"
#include "jsoncpp/include/json/json.h"

using namespace Core;

GamePtr _game = nullptr;
Json::Value _settingJson;

int Engine::execution(const GamePtr& game)
{
	if (!game) return -1;

	help::loadJson("Setting.json", _settingJson);
	
	_game = game;
	Window::create();

	return 0;
}

void Engine::close()
{
	exit(1);
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

const Json::Value& Engine::settingJson(const std::string& key)
{
	if (key.empty()) {
		return _settingJson;
	}

	if (_settingJson[key]) {
		return _settingJson[key];
	}

	return _settingJson;
}

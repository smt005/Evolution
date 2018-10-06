
#include "Engine.h"
#include "Game.h"
#include "Window.h"
#include "Common/Help.h"
#include "jsoncpp/include/json/json.h"

#include <chrono>
#include <iostream>

using namespace Core;

GamePtr _game = nullptr;
Json::Value _settingJson;
float _deltaTime = 0.0f;
double _lastTime = Engine::currentTime();

int Engine::execution(const GamePtr& game)
{
	if (!game) return -1;

	if (!help::loadJson("Setting.json", _settingJson))
	{
		_settingJson.clear();
		_settingJson["window"]["width"] = 960;
		_settingJson["window"]["height"] = 540;
		_settingJson["window"]["title"] = "Window_default";
		_settingJson["window"]["fullscreen"] = false;
		help::saveJson("Setting.json", _settingJson);
	}

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

	double currentTime = Core::Engine::currentTime();
	double deltaTime = currentTime - _lastTime;
	_lastTime = currentTime;
	_deltaTime = static_cast<float>(deltaTime / 1000);

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

double Engine::currentTime()
{
	std::chrono::milliseconds ms;
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	double value = ms.count();
	return value;
}

float Engine::deltaTime()
{
	return _deltaTime;
}

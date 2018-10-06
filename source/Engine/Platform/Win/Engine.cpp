
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

void Engine::update(const float dt)
{
	if (!_game) return;
	_game->update(dt);
}

void Engine::draw(const float dt)
{
	if (!_game) return;
	_game->draw(dt);
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

float Engine::getCurrentTime()
{
	/*{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::milliseconds ms;
		typedef std::chrono::duration<float> fsec;
		auto t0 = Time::now();
		auto t1 = Time::now();
		fsec fs = t1 - t0;
		ms d = std::chrono::duration_cast<ms>(fs);
		std::cout << fs.count() << "s\n";
		std::cout << d.count() << "ms\n";

		auto value0 = fs.count();
		auto value1 = d.count();
	}

	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;
	auto t0 = Time::now();
	auto t1 = Time::now();
	fsec fs = t0;
	ms d = std::chrono::duration_cast<ms>(fs);

	return t0.count();*/

	std::chrono::milliseconds ms;
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	return ms.count();
}


#pragma once


#include <string>
#include <memory>
#include <ctime>
#include "jsoncpp/include/json/json.h"

#include "Game.h"

class Window;

namespace Core
{

class Engine
{
public:
	static int execution(const GamePtr& game);
	static void close();

	static void init();
	static void update(const float dt);
	static void draw(const float dt);
	static void log(const std::string& text);
	static const Json::Value& settingJson(const std::string& key);
	static float getCurrentTime();
};

};	// Core
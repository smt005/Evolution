
#pragma once


#include <string>
#include "jsoncpp/include/json/json.h"

class Game;
class Window;

namespace Core
{

class Engine
{
public:
	static int execution(Game* game);
	static void exit();

	static void init();
	static void update();
	static void draw();
	static void log(const std::string& text);
	static const Json::Value& settingJson(const std::string& key);

private:
	static Game* _game;
};

};	// Core
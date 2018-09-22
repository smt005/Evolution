
#pragma once

#include <string>

class Game;
class Window;

namespace Core
{

class Engine
{
public:
	static int execution(Game* game);
	static void exit();

	static void update();
	static void log(const std::string& text);

private:
	static Game* _game;
	static Window* _window;
};

};	// Core
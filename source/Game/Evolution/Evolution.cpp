
#include "Evolution.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Common/Draw/Draw.h"
#include "../../Engine/FileSystem.h"

Evolution::Evolution()
{

}

Evolution::~Evolution()
{

}

void Evolution::init()
{
	{
		char data[] = "qweasdzxc";
		if (FileSystem::writeTextFile("test.txt", data)) {
			Core::Engine::log("WRITE: " + std::string(data));
		}
	}

	{
		int lenght = 0;
		char* data = nullptr;

		if (FileSystem::readTextFile("test.txt", data, lenght) && data) {
			Core::Engine::log("READ: " + std::string(data));
		}
	}

	Draw::setClearColor(0.3f, 0.6f, 0.9f, 1.0f);
	Draw::prepare();
}

void Evolution::update()
{
	updateGame();
}

void Evolution::updateGame()
{
	
}

void Evolution::draw()
{
	Draw::clearColor();
	Draw::drawBackround();
}

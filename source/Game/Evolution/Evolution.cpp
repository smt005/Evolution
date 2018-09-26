
#include "Evolution.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Common/Draw/Draw.h"
#include "../../Engine/Common/Draw/Shader.h"
#include "../../Engine/FileManager.h"

Evolution::Evolution()
{

}

Evolution::~Evolution()
{

}

void Evolution::init()
{
	FileManager::setResourcesDir("..\\Res");

	{
		std::string text;

		text = "current_path = " + std::filesystem::current_path().string() + "\n";
		text += "resourcesDir = " + FileManager::getResourcesDir().string() + "\n";

		if (FileManager::writeTextFile("test.txt", text)) {
			Core::Engine::log("WRITE: " + text);
		}
	}

	{
		int lenght = 0;
		char* data = nullptr;

		if (FileManager::readTextFile("test.txt", data, lenght) && data) {
			Core::Engine::log("READ: " + std::string(data));
		}
	}

	{
		unsigned int program = Shader::getShaderProgram("base.ver", "base.frag");
		Draw::setClearColor(0.3f, 0.6f, 0.9f, 1.0f);
		Draw::prepare();
	}
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

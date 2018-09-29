
#include <iostream>
#include <fstream>

#include "jsoncpp/include/json/json.h"
#include <glm/glm.hpp>
#include "glm/mat4x4.hpp"

#include "../../Engine/Engine.h"
#include "Evolution.h"

#include "Engine.h"
#include "FileManager.h"
#include "Draw/Draw.h"
#include "Draw/Camera.h"
#include "Draw/Shader.h"
#include "Object/Mesh.h"
#include "Common/Help.h"

const unsigned short int countVertex = 4;
float vertexes[12] = { 2.5f, 2.5f, 0.0f,
						2.5, -2.5f, 0.0f,
						2.5f, 2.5f, 0.0f,
						2.5f, -2.5f, 0.0f };

float vormals[12] = { 0.0f, 0.0f, 1.0f,
						0.0f, 0.0f, 1.0f,
						0.0f, 0.0f, 1.0f,
						0.0f, 0.0f, 1.0f };

float texCoorde[8] = { -2.0f, 3.0f,
						-2.0f, -2.0f,
						3.0f, 3.0f,
						3.0f, -2.0f };

unsigned short int countIndex = 2;
unsigned short indexes[6] = { 1, 2, 3, 4, 3, 2 };

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
		Draw::setClearColor(0.3f, 0.6f, 0.9f, 1.0f);
		//Draw::prepare();
	}

	_mesh = new Mesh();
	_mesh->setData(vertexes, vormals, texCoorde, countVertex, indexes, countIndex);

	Camera::current.setFromEye(true);
	Camera::current.setPos(glm::vec3(0.0f));
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
	Draw::drawBackround();
	Draw::clearColor();

	//Draw::prepare();

	/*if (_mesh) {
		glm::mat4x4 matrix(1.0f);
		Draw::draw(*_mesh, matrix);
	}*/

	Draw::drawTriangleExample();
}


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
#include "Callback/Callback.h"
#include "Object/Object.h"

Callback* callback = nullptr;
Object* object = nullptr;

Evolution::Evolution()
{

}

Evolution::~Evolution()
{
	if (callback) {
		delete callback;
		callback = nullptr;
	}

	if (object) {
		delete object;
		object = nullptr;
	}
}

void Evolution::init()
{
	FileManager::setResourcesDir("..\\Res");

	Draw::setClearColor(0.3f, 0.6f, 0.9f, 1.0f);

	Camera::current.setFromEye(false);
	Camera::current.setPos(glm::vec3(0.0f, 0.0f, 0.0f));

	if (!callback)
	{
		callback = new Callback(Callback::Type::ON_RELEASE_TAP, []() {
			float distCamera = Camera::current.dist();
			distCamera += 1.0f;
			Camera::current.setDist(distCamera);

		});
	}

	if (!object)
	{
		object = new Object("Object", "Box1");
	}
}

void Evolution::update()
{
}

void Evolution::draw()
{
	Draw::drawBackround();
	Draw::clearColor();

	Draw::prepare();
	Draw::draw(*object);

	//Draw::drawTriangleExample();
}

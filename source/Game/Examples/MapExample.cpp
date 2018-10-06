
#include <iostream>
#include <fstream>

#include "jsoncpp/include/json/json.h"
#include <glm/glm.hpp>
#include "glm/mat4x4.hpp"

#include "../../Engine/Engine.h"
#include "MapExample.h"

#include "Engine.h"
#include "FileManager.h"
#include "Draw/Draw.h"
#include "Draw/Camera.h"
#include "Draw/Shader.h"
#include "Object/Mesh.h"
#include "Common/Help.h"
#include "Callback/Callback.h"
#include "Object/Object.h"
#include "Object/Map.h"

MapExample::~MapExample()
{
	if (!_callback) {
		delete _callback;
		_callback = nullptr;
	}

	if (_mapGame) {
		delete _mapGame;
		_mapGame = nullptr;
	}
}

void MapExample::init()
{
	FileManager::setResourcesDir("..\\Res");

	Draw::setClearColor(0.9f, 0.6f, 0.3f, 1.0f);

	Camera::current.setFromEye(false);
	Camera::current.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	Camera::current.setDist(1.0f);

	if (!_callback) {
		_callback = new Callback(CallbackType::PINCH_TAP, [](const CallbackEventPtr& callbackEventPtr) {
			Camera::current.rotate(Callback::deltaMousePos());
		});
	}

	if (!_mapGame) {
		_mapGame = new Map("Examples/MapExample");
	}
}

void MapExample::update(const float dt)
{
	if (_mapGame) {
		_mapGame->action();
	}
}

void MapExample::draw(const float dt)
{
	Draw::viewport();
	Draw::clearColor();
	Draw::prepare();

	if (_mapGame) {
		Draw::draw(*_mapGame);
	}
}

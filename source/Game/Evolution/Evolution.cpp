
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
#include "Object/ShapeTriangles.h"
#include "Common/Help.h"
#include "Callback/Callback.h"
#include "Object/Object.h"
#include "Object/Map.h"

ShapeTriangles shapeTriangles;

Evolution::~Evolution()
{
	if (!_callback) {
		delete _callback;
		_callback = nullptr;
	}

	if (!_mapGame) {
		delete _mapGame;
		_mapGame = nullptr;
	}
}

void Evolution::init()
{
	FileManager::setResourcesDir("..\\Res");

	Draw::setClearColor(0.3f, 0.6f, 0.9f, 1.0f);

	Camera::current.setFromEye(false);
	Camera::current.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	Camera::current.setDist(1.0f);

	if (!_mapGame) {
		_mapGame = new Map("Evolution");
	}

	ShapeTriangles::makeTriangle(shapeTriangles, 10.0f);

	initCallback();
}

void Evolution::initCallback()
{
	if (!_callback) {
		_callback = new Callback(CallbackType::PINCH_TAP, [](const CallbackEventPtr& callbackEventPtr) {
			if (Callback::pressTap(VirtualTap::RIGHT)) {
				Camera::current.rotate(Callback::deltaMousePos());
			}

			if (Callback::pressTap(VirtualTap::MIDDLE)) {
				Camera::current.move(Callback::deltaMousePos() * 10000.0f);
			}
		});

		_callback->add(CallbackType::RELEASE_KEY, [](const CallbackEventPtr& callbackEventPtr) {
			KeyCallbackEvent* releaseKeyEvent = (KeyCallbackEvent*)callbackEventPtr->get();
			VirtualKey key = releaseKeyEvent->getId();

			if (key == VirtualKey::ESCAPE) {
				Core::Engine::close();
			}
		});

		_callback = new Callback(CallbackType::PINCH_KEY, [](const CallbackEventPtr& callbackEventPtr) {
			float speedCamera = 0.1f;
			if (Callback::pressKey(VirtualKey::SHIFT)) {
				speedCamera = 0.125f;
			}

			if (Callback::pressKey(VirtualKey::S)) {
				Camera::current.move(CAMERA_FORVARD, speedCamera);
			}

			if (Callback::pressKey(VirtualKey::W)) {
				Camera::current.move(CAMERA_BACK, speedCamera);
			}

			if (Callback::pressKey(VirtualKey::D)) {
				Camera::current.move(CAMERA_RIGHT, speedCamera);
			}

			if (Callback::pressKey(VirtualKey::A)) {
				Camera::current.move(CAMERA_LEFT, speedCamera);
			}

			if (Callback::pressKey(VirtualKey::R)) {
				Camera::current.move(CAMERA_TOP, speedCamera);
			}

			if (Callback::pressKey(VirtualKey::F)) {
				Camera::current.move(CAMERA_DOWN, speedCamera);
			}
		});
	}
}

void Evolution::update()
{
	if (_mapGame) {
		_mapGame->action();
	}
}

void Evolution::draw()
{
	Draw::clearColor();
	Draw::prepare();

	if (_mapGame) {
		//Draw::draw(*_mapGame);
	}

	Draw::draw(shapeTriangles);
}

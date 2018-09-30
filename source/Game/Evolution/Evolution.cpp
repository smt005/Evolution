
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
#include "Object/Map.h"

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

	initCallback();
}

void Evolution::initCallback()
{
	if (!_callback) {
		_callback = new Callback(CallbackType::PINCH_TAP, [](const CallbackEventPtr& callbackEventPtr) {
			Camera::current.rotate(CallbackHandler::deltaMousePos());
		});

		_callback->add(CallbackType::RELEASE_KEY, [](const CallbackEventPtr& callbackEventPtr) {
			ReleaseKeyEvent* releaseKeyEvent = (ReleaseKeyEvent*)callbackEventPtr->get();
			int key = releaseKeyEvent->getKey();

			if (key == VirtualKey::ESCAPE) {
				Core::Engine::close();
			}
		});

		_callback = new Callback(CallbackType::PINCH_KEY, [](const CallbackEventPtr& callbackEventPtr) {
			float speedCamera = 0.1f;
			if (CallbackHandler::pressKey(VirtualKey::SHIFT)) {
				speedCamera = 0.125f;
			}

			if (CallbackHandler::pressKey(VirtualKey::S)) {
				Camera::current.move(CAMERA_FORVARD, speedCamera);
			}

			if (CallbackHandler::pressKey(VirtualKey::W)) {
				Camera::current.move(CAMERA_BACK, speedCamera);
			}

			if (CallbackHandler::pressKey(VirtualKey::D)) {
				Camera::current.move(CAMERA_RIGHT, speedCamera);
			}

			if (CallbackHandler::pressKey(VirtualKey::A)) {
				Camera::current.move(CAMERA_LEFT, speedCamera);
			}

			if (CallbackHandler::pressKey(VirtualKey::R)) {
				Camera::current.move(CAMERA_TOP, speedCamera);
			}

			if (CallbackHandler::pressKey(VirtualKey::F)) {
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
		Draw::draw(*_mapGame);
	}
}

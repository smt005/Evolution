
#include <iostream>
#include <fstream>
#include <vector>

#include "jsoncpp/include/json/json.h"
#include <glm/glm.hpp>
#include "glm/mat4x4.hpp"

#include "Evolution.h"

#include "Core.h"
#include "FileManager.h"
#include "Draw/Draw.h"
#include "Draw/DrawLine.h"
#include "Draw/Camera.h"
#include "Draw/Shader.h"
#include "Object/Mesh.h"
#include "Object/ShapeTriangles.h"
#include "Common/Help.h"
#include "Callback/Callback.h"
#include "Object/Object.h"
#include "Object/Map.h"
#include "Microbe/Microbe.h"

DrawLine lineAdd;

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
	Engine::FileManager::setResourcesDir("..\\Res");

	Draw::setClearColor(0.3f, 0.6f, 0.9f, 1.0f);

	Camera::current.setFromEye(true);
	Camera::current.setPos(glm::vec3(0.0f, 0.0f, 10.0f));
	Camera::current.setDist(1.0f);

	if (!_mapGame) {
		_mapGame = new Map("Evolution");
	}

	Microbe::generateMicrobes(100);

	initCallback();

	lineAdd.set({ 1.0f, -0.0f, 1.0f }, { -5.0f, -20.0f, 2.0f });
}

void Evolution::initCallback()
{
	if (!_callback) {
		_callback = new Engine::Callback(Engine::CallbackType::PINCH_TAP, [](const Engine::CallbackEventPtr& callbackEventPtr) {
			if (Engine::Callback::pressTap(Engine::VirtualTap::RIGHT)) {
				Camera::current.rotate(Engine::Callback::deltaMousePos());
			}

			if (Engine::Callback::pressTap(Engine::VirtualTap::MIDDLE)) {
				Camera::current.move(Engine::Callback::deltaMousePos() * 1000.0f * Engine::Core::deltaTime());
			}
		});

		_callback->add(Engine::CallbackType::RELEASE_KEY, [](const Engine::CallbackEventPtr& callbackEventPtr) {
			Engine::KeyCallbackEvent* releaseKeyEvent = (Engine::KeyCallbackEvent*)callbackEventPtr->get();
			Engine::VirtualKey key = releaseKeyEvent->getId();

			if (key == Engine::VirtualKey::ESCAPE) {
				Engine::Core::close();
			}

			if (key == Engine::VirtualKey::Q) {
				Microbe::generateMicrobes(100);
			}
		});

		_callback = new Engine::Callback(Engine::CallbackType::PINCH_KEY, [](const Engine::CallbackEventPtr& callbackEventPtr) {
			float speedCamera = 10.0f * Engine::Core::deltaTime();
			if (Engine::Callback::pressKey(Engine::VirtualKey::SHIFT)) {
				speedCamera = 0.125f * Engine::Core::deltaTime();
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::W)) {
				Camera::current.move(CAMERA_FORVARD, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::S)) {
				Camera::current.move(CAMERA_BACK, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::A)) {
				Camera::current.move(CAMERA_RIGHT, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::D)) {
				Camera::current.move(CAMERA_LEFT, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::R)) {
				Camera::current.move(CAMERA_TOP, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::F)) {
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

	Microbe::update();
}

void Evolution::draw()
{
	Draw::viewport();
	Draw::clearColor();

	// DrawLine

	DrawLine::prepare();

	for (auto& microbe : Microbe::microbes()) {
		if (microbe) {
			glm::mat4x4 matrix = glm::scale(microbe->getMatrix(), microbe->getScale());

			DrawLine line({ matrix[3][0], matrix[3][1], matrix[3][2] }, { matrix[3][0], matrix[3][1], matrix[3][2] + 1.0f } );
			line.setColor(Color::RED);
			line.draw();
		}
	}

	//	Draw

	Draw::prepare();

	if (_mapGame) {
		Draw::draw(*_mapGame);
	}

	for (auto& microbe : Microbe::microbes()) {
		if (microbe) {
			glm::mat4x4 matrix = glm::scale(microbe->getMatrix(), microbe->getScale());
			Draw::draw(microbe->shape(), matrix);
		}
	}

	//	DrawLine

	DrawLine::prepare();

	{
		DrawLine line(glm::vec3(0.0f, -2.0f, 1.0f), glm::vec3(2.0f, 8.0f, 20.0f));
		line.setColor({1.0f, 0.0f, 0.0});
		line.setLineWidth(3.0f);

		Color color(Color::RED);
		color.setBlue(1.0f);

		line.draw();
	}

	{
		lineAdd.setColor(Color::GREEN);
		lineAdd.draw();
	}
}

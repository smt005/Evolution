
#include <iostream>
#include <fstream>

#include "jsoncpp/include/json/json.h"
#include <glm/glm.hpp>
#include "glm/mat4x4.hpp"

#include "MapExample.h"

#include "Core.h"
#include "FileManager.h"
#include "Draw/Draw.h"
#include "Draw/DrawLine.h"
#include "Draw/Camera.h"
#include "Draw/Shader.h"
#include "Object/Mesh.h"
#include "Common/Help.h"
#include "Callback/Callback.h"
#include "Object/Object.h"
#include "Object/Map.h"
#include "Object/Line.h"
#include "Object/Triangle.h"

const std::string saveFileName("Data/MapExampleSave.json");
const std::string mapFileName("Examples/MapExample");

Greed greed(100.0f, 10.0f);
Triangle triangle;

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
	Engine::FileManager::setResourcesDir("..\\Res");
	if (!load())
	{
		Camera::current.setFromEye(true);
		Camera::current.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
		Camera::current.setDist(1.0f);
	}

	Draw::setClearColor(0.9f, 0.6f, 0.3f, 1.0f);

	if (!_mapGame) {
		_mapGame = new Map(mapFileName);
	}

	greed.setPos({0.0f, 0.0f, 0.1f});

	//Triangle::makeTriangle(triangle);

	Triangle::Template t0;

	//	dist, scale vector
	{
		Triangle::Template& t1 = t0.add(0.9f, 0.75f, glm::vec3(1.0f, 0.0f, 0.0f));
		{
			t1.add(1.3f, 0.5f, glm::vec3(0.7f, 0.0f, 0.0f));
			t1.add(0.9f, 0.25f, glm::vec3(0.2f, -1.0f, 0.0f));
		}
	}
	{
		Triangle::Template& t1 = t0.add(0.8f, 0.6f, glm::vec3(1.0f, 1.0f, 0.0f));
		{
			t1.add(0.5f, 0.15f, glm::vec3(-0.4f, 0.5f, 0.0f));
			t1.add(1.25f, 0.5f, glm::vec3(0.5f, -0.7f, 0.0f));
			t1.add(1.0f, 0.8f, glm::vec3(0.25f, 0.57f, 0.0f));
		}
	}

	Triangle::make(triangle, t0);

	triangle.setTexture("Textures/Cell.png");
	triangle.setPos({0.5f, 0.25f, 0.5f});
	
	initCallback();
}

void MapExample::initCallback()
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

		_callback->add(Engine::CallbackType::RELEASE_KEY, [this](const Engine::CallbackEventPtr& callbackEventPtr) {
			Engine::KeyCallbackEvent* releaseKeyEvent = (Engine::KeyCallbackEvent*)callbackEventPtr->get();
			Engine::VirtualKey key = releaseKeyEvent->getId();

			if (key == Engine::VirtualKey::ESCAPE) {
				Engine::Core::close();
			}

			if (key == Engine::VirtualKey::S && Engine::Callback::pressKey(Engine::VirtualKey::CONTROL)) {
				save();
			}

			if (key == Engine::VirtualKey::L && Engine::Callback::pressKey(Engine::VirtualKey::CONTROL)) {
				load();
			}
		});

		_callback = new Engine::Callback(Engine::CallbackType::PINCH_KEY, [](const Engine::CallbackEventPtr& callbackEventPtr) {
			if (Engine::Callback::pressKey(Engine::VirtualKey::CONTROL)) {
				return;
			}

			float speedCamera = 40.0f * Engine::Core::deltaTime();
			if (Engine::Callback::pressKey(Engine::VirtualKey::SHIFT)) {
				speedCamera = 10.0f * Engine::Core::deltaTime();
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::S)) {
				Camera::current.move(CAMERA_FORVARD, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::W)) {
				Camera::current.move(CAMERA_BACK, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::D)) {
				Camera::current.move(CAMERA_RIGHT, speedCamera);
			}

			if (Engine::Callback::pressKey(Engine::VirtualKey::A)) {
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

bool MapExample::load()
{
	Json::Value saveData;
	if (!help::loadJson(saveFileName, saveData) || saveData.empty()) {
		return false;
	}

	if (!saveData["camera"].empty()) {
		Json::Value& cameraData = saveData["camera"];
		Camera::current.setJsonData(cameraData);
	}

	Engine::Core::log("LOAD");
	return true;
}

void MapExample::save()
{
	Json::Value saveData;

	Json::Value cameraData;
	Camera::current.getJsonData(cameraData);

	saveData["camera"] = cameraData;
	saveData["testKey"] = "testValue";

	help::saveJson(saveFileName, saveData);

	Engine::Core::log("SAVE");
}

void MapExample::update()
{
	if (_mapGame) {
		_mapGame->action();
	}
}

void MapExample::draw()
{
	Draw::viewport();
	Draw::clearColor();

	//	DrawLine

	draw::DrawLine::prepare();

	{
		float points[] = {	0.0f, 0.0f, 0.0f, 10.0f, 20.0f, 20.0f,
							10.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f };
		Line line(points, 4, Line::LINE);
		line.setLineWidth(5.0f);
		line.color = Color::GREEN;

		draw::DrawLine::draw(line);
	}

	{
		float points[] = {	20.0f, 30.0f, 0.0f,
							20.0f, 30.0f, 20.0f,
							30.0f, 30.0f, 20.0f };
		Line line(points, 3, Line::LOOP);
		line.setLineWidth(5.0f);
		line.color = { 0.3f, 0.6f, 0.9f,0.5f };

		draw::DrawLine::draw(line);
	}

	{
		float points[] = {	30.0f, 40.0f, 0.0f,
							30.0f, 40.0f, 20.0f,
							40.0f, 40.0f, 20.0f };
		Line line(points, 3, Line::STRIP);
		line.setLineWidth(5.0f);
		line.color = Color::RED;
		line.color.setAlpha(0.5);

		draw::DrawLine::draw(line);
	}

	draw::DrawLine::draw(greed);

	// Draw

	Draw::prepare();

	if (_mapGame) {
		Draw::draw(*_mapGame);
	}

	Draw::draw(triangle);
}

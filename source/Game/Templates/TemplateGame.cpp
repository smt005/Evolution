
#include "TemplateGame.h"

#include "jsoncpp/include/json/json.h"
#include <glm/glm.hpp>
#include "glm/mat4x4.hpp"

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
#include "Object/Color.h"
#include "Object/Identify.h"

TemplateGame::TemplateGame()
{
}

TemplateGame::~TemplateGame()
{
	if (!_callback) {
		delete _callback;
		_callback = nullptr;
	}

	if (_mapGame) {
		delete _mapGame;
		_mapGame = nullptr;
	}

	if (_greed) {
		delete _greed;
		_greed = nullptr;
	}
}

std::string TemplateGame::getSaveFileName() {
	return "Saves/" + getName() + "Save.json";
}

std::string TemplateGame::getMapFileName() {
	return "Examples/MapExample";
}

void TemplateGame::init()
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
		_mapGame = new Map(getMapFileName());
	}

	_greed = new Greed(100.0f, 10.0f);

	initCallback();
}

void TemplateGame::initCallback()
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

			float speedCamera = 5.0f * Engine::Core::deltaTime();
			if (Engine::Callback::pressKey(Engine::VirtualKey::SHIFT)) {
				speedCamera = 30.0f * Engine::Core::deltaTime();
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

bool TemplateGame::load()
{
	Json::Value saveData;
	if (!help::loadJson(getSaveFileName(), saveData) || saveData.empty()) {
		return false;
	}

	if (!saveData["camera"].empty()) {
		Json::Value& cameraData = saveData["camera"];
		Camera::current.setJsonData(cameraData);
	}

#if _DEBUG
	Engine::Core::log("LOAD: " + getSaveFileName() + "\n" + help::stringFroJson(saveData));
#endif // _DEBUG

	return true;
}

void TemplateGame::save()
{
	Json::Value saveData;

	Json::Value cameraData;
	Camera::current.getJsonData(cameraData);

	saveData["camera"] = cameraData;
	saveData["testKey"] = "testValue";

	help::saveJson(getSaveFileName(), saveData);

#if _DEBUG
	Engine::Core::log("SAVE: " + getSaveFileName() + "\n" + help::stringFroJson(saveData));
#endif // _DEBUG
}

void TemplateGame::update()
{
	if (_mapGame) {
		_mapGame->action();
	}
}

void TemplateGame::draw()
{
	Draw::viewport();
	Draw::clearColor();

	//	DrawLine

	draw::DrawLine::prepare();
	draw::DrawLine::draw(*_greed);

	// Draw

	Draw::prepare();

	if (_mapGame) {
		Draw::draw(*_mapGame);
	}

}

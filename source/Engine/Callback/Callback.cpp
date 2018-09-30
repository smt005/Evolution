
#include "Callback.h"
#include "Engine.h"

std::map<int, Callback*> CallbackHandler::_objects;
glm::vec2 CallbackHandler::_mousePos;
glm::vec2 CallbackHandler::_deltaMousePos;
bool CallbackHandler::_key[CALLBACK_COUNT_KEY];
bool CallbackHandler::_tap[CALLBACK_COUNT_TAP];
CallbackEventPtr emptyCallbackEventPtr;

int tapPinch = 0;
int keyPinch = 0;

void CallbackHandler::add(Callback& object)
{
	int id = object.getId();
	_objects[id] = &object;
}

void CallbackHandler::remove(Callback& object)
{
	int id = object.getId();
	auto it = _objects.find(id);

	if (it != _objects.end()) {
		_objects.erase(it);
	}
}

void CallbackHandler::onPressKey(const int id) {
	KeyCallbackEvent* callbackEvent = new KeyCallbackEvent(static_cast<VirtualKey>(id));
	CallbackEventPtr callbackEventPtr(callbackEvent);
	iteration(CallbackType::PRESS_KEY, callbackEventPtr);

	if (id >= 0) {
		_key[id] = true;
		++keyPinch;
	}
}

void CallbackHandler::onReleaseKey(const int id) {
	if (id >= 0) {
		--keyPinch;
		_key[id] = false;
	}

	KeyCallbackEvent* callbackEvent = new KeyCallbackEvent(static_cast<VirtualKey>(id));
	CallbackEventPtr callbackEventPtr(callbackEvent);
	iteration(CallbackType::RELEASE_KEY, callbackEventPtr);
}

void CallbackHandler::onPressTap(const int id)
{
	TapCallbackEvent* callbackEvent = new TapCallbackEvent(static_cast<VirtualTap>(id));
	CallbackEventPtr callbackEventPtr(callbackEvent);
	iteration(CallbackType::PRESS_TAP, callbackEventPtr);

	if (id >= 0) {
		_tap[id] = true;
		++tapPinch;
	}
}

void CallbackHandler::onReleaseTap(const int id) {
	if (id >= 0) {
		--tapPinch;
		_tap[id] = false;
	}

	KeyCallbackEvent* callbackEvent = new KeyCallbackEvent(static_cast<VirtualKey>(id));
	CallbackEventPtr callbackEventPtr(callbackEvent);
	iteration(CallbackType::RELEASE_TAP, callbackEventPtr);
}

void CallbackHandler::onMove(float x, float y)
{
	if (!(_mousePos.x == x && _mousePos.y == y))
	{
		_deltaMousePos.x = _mousePos.x - x;
		_deltaMousePos.y = _mousePos.y - y;

		_mousePos.x = x;
		_mousePos.y = y;

		iteration(CallbackType::MOVE, emptyCallbackEventPtr);
	}
}

void CallbackHandler::update()
{
	if (keyPinch) {
		iteration(CallbackType::PINCH_KEY, emptyCallbackEventPtr);
	}

	if (tapPinch) {
		iteration(CallbackType::PINCH_TAP, emptyCallbackEventPtr);
	}

	_deltaMousePos.x = 0.0f;
	_deltaMousePos.y = 0.0f;
}

inline void CallbackHandler::iteration(const CallbackType& type, const CallbackEventPtr& callbackEventPtr)
{
	for (auto& pair : _objects) {
		auto& object = pair.second;
		object->action(type, callbackEventPtr);
	}
}

// Callback

int Callback::add(const CallbackType type, const std::function<void(const CallbackEventPtr& callbackEventPtr)>& function) {
	int id = reinterpret_cast<int>(&function);
	add(type, function, id);
	return id;
}

int Callback::add(const CallbackType type, const std::function<void(const CallbackEventPtr& callbackEventPtr)>& function, int& id) {
	if (id == 0) {
		id = reinterpret_cast<int>(&function);
	}

	auto& functions = _map[type];
	functions[id] = function;
	return id;
}

void Callback::remove(const int id) {
	for (auto& functionsMap : _map) {
		for (auto& functionsMap : _map) {
			auto& functions = functionsMap.second;
			auto it = functions.find(id);
			if (it != functions.end()) {
				functions.erase(it);
				return;
			}
		}
	}
}

void Callback::action(CallbackType type, const CallbackEventPtr& callbackEventPtr)
{
	auto it = _map.find(type);
	if (it != _map.end()) {
		auto& functions = it->second;
		for (auto& function : functions) {
			function.second(callbackEventPtr);
		}
	}
}

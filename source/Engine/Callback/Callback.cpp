
#include "Callback.h"
#include "Engine.h"

std::map<int, Callback*> CallbackHandler::_objects;

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

void CallbackHandler::onPressKey(const int key)
{
	for (auto& pair : _objects) {
		auto object = pair.second;
		object->action(Callback::Type::ON_PRESS_KEY);
	}
}

void CallbackHandler::onReleaseKey(const int key)
{
	for (auto& pair : _objects) {
		auto& object = pair.second;
		object->action(Callback::Type::ON_RELEASE_KEY);
	}
}

void CallbackHandler::onPressTap(const int key)
{
	for (auto& pair : _objects) {
		auto& object = pair.second;
		object->action(Callback::Type::ON_PRESS_TAP);
	}
}

void CallbackHandler::onReleaseTap(const int key)
{
	for (auto& pair : _objects) {
		auto& object = pair.second;
		object->action(Callback::Type::ON_RELEASE_TAP);
	}
}

// Callback

int Callback::add(const Type type, const std::function<void(void)>& function) {
	int id = reinterpret_cast<int>(&function);
	add(type, function, id);
	return id;
}

int Callback::add(const Type type, const std::function<void(void)>& function, int& id) {
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

void Callback::action(Type type)
{
	auto it = _map.find(type);
	if (it != _map.end()) {
		auto& functions = it->second;
		for (auto& function : functions) {
			function.second();
		}
	}
}


#include "Callback.h"

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
	for (auto pair : _objects) {
		auto object = pair.second;
		object->action(Callback::Type::ON_PRESS_KEY);
	}
}

void CallbackHandler::onReleaseKey(const int key)
{
	for (auto pair : _objects) {
		auto object = pair.second;
		object->action(Callback::Type::ON_RELEASE_KEY);
	}
}

void CallbackHandler::onPressTap(const int key)
{
	for (auto pair : _objects) {
		auto object = pair.second;
		object->action(Callback::Type::ON_PRESS_TAP);
	}
}

void CallbackHandler::onReleaseTap(const int key)
{
	for (auto pair : _objects) {
		auto object = pair.second;
		object->action(Callback::Type::ON_RELEASE_TAP);
	}
}

void Callback::action(Type type)
{
	auto it = _map.find(type);
	if (it != _map.end()) {
		auto functions = it->second;
		for (auto function : functions) {
			function();
		}
	}
}

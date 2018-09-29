
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

	if (it != _objects.end())
	{
		_objects.erase(it);
	}
}

void CallbackHandler::onPressKey(const int key)
{
	for (auto pair : _objects)
	{
		auto item = pair.second;
		auto functions = item->callbackFunctions();

		for (auto function : functions)
		{
			if (function.type() == CallbackFunctions::Type::ON_PRESS_KEY) {
				function.function()();
			}
			
		}
	}
}

void CallbackHandler::onReleaseKey(const int key)
{
	for (auto pair : _objects)
	{
		auto item = pair.second;
		auto functions = item->callbackFunctions();

		for (auto function : functions)
		{
			if (function.type() == CallbackFunctions::Type::ON_RELEASE_KEY) {
				function.function()();
			}

		}
	}
}

void CallbackHandler::onPressTap(const int key)
{
	for (auto pair : _objects)
	{
		auto item = pair.second;
		auto functions = item->callbackFunctions();

		for (auto function : functions)
		{
			if (function.type() == CallbackFunctions::Type::ON_PRESS_TAP) {
				function.function()();
			}

		}
	}
}

void CallbackHandler::onReleaseTap(const int key)
{
	for (auto pair : _objects)
	{
		auto item = pair.second;
		auto functions = item->callbackFunctions();

		for (auto function : functions)
		{
			if (function.type() == CallbackFunctions::Type::ON_RELEASE_TAP) {
				function.function()();
			}

		}
	}
}
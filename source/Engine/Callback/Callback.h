#pragma once

#include <map>
#include <vector>
#include <functional>
#include <memory>
#include "glm/vec2.hpp"

#include "CallbackEvent.h"
#include "VirtualKey.h"

constexpr int CALLBACK_COUNT_KEY = 1024;

class Callback;

enum class CallbackType
{
	NONE,
	PRESS_TAP,
	PINCH_TAP,
	RELEASE_TAP,
	PRESS_KEY,
	PINCH_KEY,
	RELEASE_KEY,
	MOVE
};

class CallbackHandler
{
public:
	static void add(Callback& object);
	static void remove(Callback& object);

	static void onPressKey(const int key);
	static void onReleaseKey(const int key);

	static void onPressTap(const int key);
	static void onReleaseTap(const int key);

	static void onMove(float x, float y);

	static void update();

	inline static const glm::vec2& mousePos() { return _mousePos; }
	inline static const glm::vec2& deltaMousePos() { return _deltaMousePos; }

	inline static bool pressKey(const int key) { return _key[key]; }

private:
	static void iteration(const CallbackType& type, const CallbackEventPtr& callbackEventPtr);

private:
	static std::map<int, Callback*> _objects;
	static glm::vec2 _mousePos;
	static glm::vec2 _deltaMousePos;
	static bool _key[CALLBACK_COUNT_KEY];
};

class Callback
{
public:
	Callback() {
		CallbackHandler::add(*this);
	}

	Callback(const CallbackType type, const std::function<void(const CallbackEventPtr& callbackEventPtr)>& function) {
		CallbackHandler::add(*this);
		add(type, function);
	}

	Callback(const CallbackType type, const std::function<void(const CallbackEventPtr& callbackEventPtr)>& function, int& id) {
		CallbackHandler::add(*this);
		add(type, function, id);
	}

	~Callback() {
		CallbackHandler::remove(*this);
	}

	int getId() {
		int id = reinterpret_cast<int>(this);
		return id;
	}

	int add(const CallbackType type, const std::function<void(const CallbackEventPtr& callbackEventPtr)>& function);
	int add(const CallbackType type, const std::function<void(const CallbackEventPtr& callbackEventPtr)>& function, int& id);
	void remove(const int id);
	void action(CallbackType type, const CallbackEventPtr& callbackEvent);

private:
	std::map<CallbackType, std::map<int, std::function<void(const CallbackEventPtr& callbackEventPtr)>>> _map;
};

#pragma once

#include <map>
#include <vector>
#include <functional>

class Callback;

class CallbackHandler
{
public:
	static void add(Callback& object);
	static void remove(Callback& object);

	static void onPressKey(const int key);
	static void onReleaseKey(const int key);
	
	static void onPressTap(const int key);
	static void onReleaseTap(const int key);

private:
	static std::map<int, Callback*> _objects;

};

class Callback
{
public:
	enum class Type
	{
		NONE,
		ON_PRESS_TAP,
		ON_RELEASE_TAP,
		ON_PRESS_KEY,
		ON_RELEASE_KEY
	};

	Callback() {
		CallbackHandler::add(*this);
	}

	Callback(const Type type, const std::function<void(void)>& function) {
		CallbackHandler::add(*this);
		add(type, function);
	}

	~Callback() {
		CallbackHandler::remove(*this);
	}

	int getId() {
		int id = reinterpret_cast<int>(this);
		return id;
	}

	void add(const Type type, const std::function<void(void)>& function) {
		std::vector<std::function<void(void)>>& functions = _map[type];
		functions.push_back(function);
	}

	void action(Type type);

private:
	std::map<Type, std::vector<std::function<void(void)>>> _map;
};

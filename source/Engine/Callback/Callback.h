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

	Callback(const Type type, const std::function<void(void)>& function, int& id) {
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

	int add(const Type type, const std::function<void(void)>& function);
	int add(const Type type, const std::function<void(void)>& function, int& id);
	void remove(const int id);
	void action(Type type);

private:
	std::map<Type, std::map<int, std::function<void(void)>>> _map;
};

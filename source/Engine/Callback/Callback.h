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

class CallbackFunctions
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

	CallbackFunctions() {}
	CallbackFunctions(const Type type, const std::function<void(void)>& function)
	{
		_type = type;
		_function = function;
	}

	inline Type type() { return _type; }
	inline std::function<void(void)> function() { return _function; }

private:
	Type _type = Type::NONE;
	std::function<void(void)> _function;
};

class Callback
{
public:
	Callback() {
		CallbackHandler::add(*this);
	}

	Callback(const CallbackFunctions& callbackFunction) {
		CallbackHandler::add(*this);
		add(callbackFunction);
	}

	Callback(const CallbackFunctions::Type type, const std::function<void(void)>& function) {
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

	void add(const CallbackFunctions::Type type, const std::function<void(void)>& function)
	{
		CallbackFunctions callbackFunction(type, function);
		add(callbackFunction);
	}

	void add(const CallbackFunctions& callbackFunction)
	{
		_callbackFunctions.push_back(callbackFunction);
	}

	inline std::vector<CallbackFunctions>& callbackFunctions() { return _callbackFunctions; }

private:
	std::vector<CallbackFunctions> _callbackFunctions;
};

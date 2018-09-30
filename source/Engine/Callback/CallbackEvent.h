#pragma once

#include <map>
#include <vector>
#include <functional>
#include <memory>

class CallbackEvent
{
public:
	virtual ~CallbackEvent() {}
	CallbackEvent* get() { return this; }
};

typedef std::shared_ptr<CallbackEvent> CallbackEventPtr;

class ReleaseKeyEvent : public CallbackEvent
{
public:
	ReleaseKeyEvent(const int& key) { _key = key; }
	inline int getKey() { return _key; }

public:
	int _key;

};

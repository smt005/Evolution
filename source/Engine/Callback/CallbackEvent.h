#pragma once

#include <map>
#include <vector>
#include <functional>
#include <memory>

#include "VirtualKey.h"

class CallbackEvent
{
public:
	virtual ~CallbackEvent() {}
	CallbackEvent* get() { return this; }
};

typedef std::shared_ptr<CallbackEvent> CallbackEventPtr;

class KeyCallbackEvent : public CallbackEvent
{
public:
	KeyCallbackEvent(const VirtualKey id) { _id = id; }
	inline VirtualKey getId() { return _id; }

public:
	VirtualKey _id;
};

class TapCallbackEvent : public CallbackEvent
{
public:
	TapCallbackEvent(const VirtualTap id) { _id = id; }
	inline VirtualTap getId() { return _id; }

public:
	VirtualTap _id;
};

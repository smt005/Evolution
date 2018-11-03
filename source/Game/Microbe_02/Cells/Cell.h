#pragma once

#include "MicrobeEvent_02.h"

class Microbe_02;

class Cell
{
public:
	Cell() : _consumption(0.1f) { }
	virtual ~Cell() { }
	void setCore(Microbe_02* core) {
		_core = core;
	}
	virtual void action() = 0;

protected:
	Microbe_02* _core;
	float _consumption;
};

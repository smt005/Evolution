#pragma once

#include <glm/vec3.hpp>

class Microbe_02;

class Cell
{
public:
	Cell() : _consumption(0.1f) { }
	virtual ~Cell() { }
	void setCore(Microbe_02* core) {
		_core = core;
	}
	virtual void action() {};

protected:
	Microbe_02* _core;
	float _consumption;
};

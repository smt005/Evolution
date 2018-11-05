#pragma once

#include <glm/vec3.hpp>

class Microbe_02;

class Cell
{
public:
	Cell()
	: _consumption(1.0f)
	, _stockEnergy(100.0f)
	, _maxStockEnergy(100.0f) { }
	virtual ~Cell() { }
	void setCore(Microbe_02* core) {
		_core = core;
	}
	virtual void action() {};
	bool requestEnergy();

public:
	Microbe_02* _core;
	float _consumption;
	float _stockEnergy;
	float _maxStockEnergy;
};

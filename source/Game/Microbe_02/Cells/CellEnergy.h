#pragma once

#include "Cell.h"

class Microbe_02;

class CellEnergy final : public Cell
{
public:
	CellEnergy() {
		init();
	}
	CellEnergy(Microbe_02* core) {
		_core = core;
		init();
	}
	~CellEnergy() {}

	void init() {
		_maxCapacity = 100.0f;
		_occupancy = 100.0f;
	}

	void action() override {}
	
private:
	float _maxCapacity;
	float _occupancy;
};

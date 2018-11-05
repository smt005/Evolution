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
		_maxStockEnergy = 1000.0f;
		_stockEnergy = _maxStockEnergy;
	}

	void action() override;
};

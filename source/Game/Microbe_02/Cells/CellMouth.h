#pragma once

#include "Cell.h"

class Microbe_02;

class CellMouth final : public Cell
{
public:
	CellMouth() {
		init();
	}
	CellMouth(Microbe_02* core) {
		_core = core;
		init();
	}
	~CellMouth() {}

	void init() {}
	void action() override {}
	
private:

};

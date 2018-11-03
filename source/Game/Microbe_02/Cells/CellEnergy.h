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

	void init();
	void action() override;
	
private:

};

void CellEnergy::init()
{

}

void CellEnergy::action()
{

}

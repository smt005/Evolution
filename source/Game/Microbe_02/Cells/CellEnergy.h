#pragma once

#include "Cell.h"

class CellEnergy final : public Cell
{
public:
	CellEnergy();
	~CellEnergy();

	void init();
	void action() override;
	
private:

};

CellEnergy::CellEnergy() {
	init();
}

CellEnergy::~CellEnergy()
{
}

void CellEnergy::init()
{

}

void CellEnergy::action()
{

}

#pragma once

#include "Cell.h"

class CellBrain final : public Cell
{
public:
	CellBrain();
	~CellBrain();

	void init();
	void action() override;

private:

};

CellBrain::CellBrain() {
	init();
}

CellBrain::~CellBrain()
{
}

void CellBrain::init()
{

}

void CellBrain::action()
{

}

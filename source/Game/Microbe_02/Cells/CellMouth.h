#pragma once

#include "Cell.h"

class CellMouth final : public Cell
{
public:
	CellMouth();
	~CellMouth();

	void init();
	void action() override;
	
private:

};

CellMouth::CellMouth() {
	init();
}

CellMouth::~CellMouth()
{
}

void CellMouth::init()
{

}

void CellMouth::action()
{

}

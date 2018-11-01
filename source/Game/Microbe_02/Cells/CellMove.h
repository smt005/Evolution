#pragma once

#include "Cell.h"

class CellMove final  : public Cell
{
public:
	CellMove();
	~CellMove();

	void init();
	void action() override;
	
private:

};

CellMove::CellMove() {
	init();
}

CellMove::~CellMove()
{
}

void CellMove::init()
{

}

void CellMove::action()
{

}

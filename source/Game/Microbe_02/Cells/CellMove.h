#pragma once

#include "Cell.h"

class Microbe_02;

class CellMove final  : public Cell
{
public:
	CellMove() {
		init();
	}
	CellMove(Microbe_02* core) {
		_core = core;
		init();
	}
	~CellMove() {}

	void init();
	void action() override;
	
private:

};

void CellMove::init()
{

}

void CellMove::action()
{
	if (!_core) {
		return;
	}

	_core->addEvent(Microbe_02::MOVE);
}

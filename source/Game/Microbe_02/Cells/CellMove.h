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

	DataMoveEvent* data = new DataMoveEvent();
	data->move = glm::vec3(0.1f, 0.2f, 0.0f);
	Microbe_02::Event eventMove(data);

	_core->addEvent(eventMove);
}

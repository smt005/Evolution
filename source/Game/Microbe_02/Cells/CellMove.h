#pragma once

#include "Cell.h"

class Microbe_02;

class CellMove final : public Cell
{
public:
	CellMove()
		: vectorMove(glm::vec3(0.0f, 0.0f, 0.0f)) {
		init();
	}
	CellMove(Microbe_02* core) {
		_core = core;
		init();
	}
	~CellMove() {}

	void init() { }
	void action() override;
	
public:
	glm::vec3 vectorMove;
};

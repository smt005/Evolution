#pragma once

#include "Cell.h"

class Microbe_02;

class CellBrain final : public Cell
{
public:
	CellBrain() {
		init();
	}
	CellBrain(Microbe_02* core) {
		_core = core;
		init();
	}
	
	~CellBrain() {}

	void init();
	void action() override;

public:
	static glm::vec3 targetPos;
};

#pragma once

#include "Cell.h"
#include "Neurons/NeuronTest.h"

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
	
	~CellBrain() {
		if (brain) {
			delete brain;
		}
	}

	void init();
	void action() override;
	glm::vec3 vectorToFood();

public:
	static glm::vec3 targetPos;
	Brain* brain = nullptr;
};

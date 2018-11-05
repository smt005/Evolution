#pragma once

#include "Cell.h"
#include <memory>

class Microbe_02;
class Food_02;
typedef std::shared_ptr<Food_02> Food_02Ptr;

class CellMouth final : public Cell
{
public:
	CellMouth() {
		init();
	}
	CellMouth(Microbe_02* core) {
		_core = core;
		init();
	}
	~CellMouth() {}

	void init() {}
	void action() override;
	Food_02Ptr contactToFood();
};

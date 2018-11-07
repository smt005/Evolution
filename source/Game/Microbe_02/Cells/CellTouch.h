#pragma once

#include "Cell.h"

class Microbe_02;

class CellTouch final : public Cell
{
public:
	CellTouch() {
		init();
	}
	CellTouch(Microbe_02* core) {
		_core = core;
		init();
	}

	~CellTouch() {}

	void init();
	void action() override;

public:
};

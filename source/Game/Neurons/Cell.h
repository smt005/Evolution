#pragma once

#include "Cell.h"
#include <memory>

class Microbe;
class Cell;
typedef std::shared_ptr<Cell> CellPtr;

class Cell
{
public:
	Cell() : _core(nullptr) {}
	virtual ~Cell() { }
	virtual void action() = 0;
	virtual void init(Microbe* core) { _core = core; }

public:
	Microbe* _core;
};

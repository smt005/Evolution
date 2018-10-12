#pragma once

#include "Microbe.h"

namespace microbe
{

class Brain : public Cell
{
public:
	Brain() {}
	unsigned short int type() override { return Cell::BRAIN; }

	void update() override;
};

};	// microbe
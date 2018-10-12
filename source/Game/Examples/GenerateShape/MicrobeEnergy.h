#pragma once

#include "Microbe.h"

namespace microbe
{

class Energy final : public Cell
{
public:
	Energy() {}
	unsigned short int type() override { return Cell::ENERGY; }

	void update() override;
};

};	// microbe
#pragma once

#include "Microbe.h"

namespace microbe
{

class Energy final : public Cell
{
public:
	Energy() {}
	Energy(const MicrobeWptr& core, const DNA::ValueCell& valueCell) { init(core, valueCell); }
	unsigned short int type() override { return Cell::ENERGY; }

	void update() override;
};

};	// microbe
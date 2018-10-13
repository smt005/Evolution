#pragma once

#include "Microbe.h"
#include "DNA.h"

namespace microbe
{

class Brain : public Cell
{
public:
	Brain() {}
	Brain(const MicrobeWptr& core, const DNA::ValueCell& valueCell) { init(core, valueCell); }
	unsigned short int type() override { return Cell::BRAIN; }

	void update() override;
};

};	// microbe
#pragma once

#include "Microbe.h"

namespace microbe
{

class Mover final : public Cell
{
public:
	Mover() {}
	Mover(const MicrobeWptr& core, const DNA::ValueCell& valueCell) { init(core, valueCell); }
	unsigned short int type() override { return Cell::MOUTH; }

	void update() override;
};

};	// microbe

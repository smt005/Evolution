#pragma once

#include "Microbe.h"

namespace microbe
{

class Mouth final : public Cell
{
public:
	Mouth() {}
	Mouth(const MicrobeWptr& core, const DNA::ValueCell& valueCell) { init(core, valueCell); }
	unsigned short int type() override { return Cell::MOUTH; }

	void update() override;
};

};	// microbe
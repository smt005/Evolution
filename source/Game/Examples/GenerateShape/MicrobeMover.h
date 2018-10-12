#pragma once

#include "Microbe.h"

namespace microbe
{

class Mover final : public Cell
{
public:
	Mover() {}
	unsigned short int type() override { return Cell::MOUTH; }

	void update() override;
};

};	// microbe

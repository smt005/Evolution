#pragma once

#include "Microbe.h"

namespace microbe
{

class Mouth final : public Cell
{
public:
	Mouth() {}
	unsigned short int type() override { return Cell::MOUTH; }

	void update() override;
};

};	// microbe
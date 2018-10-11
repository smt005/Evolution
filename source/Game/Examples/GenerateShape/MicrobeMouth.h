#pragma once

#include "Microbe.h"

namespace microbe
{

class Mouth final : public Cell
{
public:
	Mouth() {}
	void update() override;
};

};	// microbe
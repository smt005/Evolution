#pragma once

#include "Microbe.h"

namespace microbe
{

class Mover final : public Cell
{
public:
	Mover() {}
	void update() override;
};

};	// microbe

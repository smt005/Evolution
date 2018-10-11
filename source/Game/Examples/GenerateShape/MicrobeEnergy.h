#pragma once

#include "Microbe.h"

namespace microbe
{

class Energy final : public Cell
{
public:
	Energy() {}
	void update() override;
};

};	// microbe
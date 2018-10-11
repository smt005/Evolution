#pragma once

#include "Microbe.h"

namespace microbe
{

class Brain : public Cell
{
public:
	Brain() {}
	void update() override;
};

};	// microbe
#pragma once

#include "Microbe.h"

namespace microbe
{

class Mover final : public Cell
{
public:
	Mover() {}
	Mover(const MicrobeWptr& core, const DNA::ValueCell& valueCell);
	unsigned short int type() override { return Cell::MOUTH; }

	void update() override;

private:
	glm::vec3 _vec;
};

};	// microbe

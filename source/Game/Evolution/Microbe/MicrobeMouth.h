#pragma once

#include "Microbe.h"

namespace microbe
{

class Mouth final : public Cell
{
public:
	Mouth() {}
	Mouth(const MicrobeWptr& core, const DNA::ValueCell& valueCell);
	unsigned short int type() override { return Cell::MOUTH; }

	void update() override;
	void eat();

private:
	float _valueNeed;
	float _valueDamage;
	MicrobePtr _target;

};

};	// microbe
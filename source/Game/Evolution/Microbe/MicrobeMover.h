#pragma once

#include "Microbe.h"

namespace microbe
{

class Mover final : public Cell
{
public:
	Mover() : _state(false), _valueWant(1.0f) {}
	Mover(const MicrobeWptr& core, const DNA::ValueCell& valueCell);
	unsigned short int type() override { return Cell::MOUTH; }
	inline void setState(const bool state) { _state  = state; }
	void update() override;

private:
	bool _state;
	glm::vec3 _vec;
	float _valueWant;
};

};	// microbe

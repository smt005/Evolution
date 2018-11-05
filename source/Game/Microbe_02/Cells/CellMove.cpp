#pragma once

#include "CellMove.h"
#include "Microbe_02/Microbe_02.h"
#include "Microbe_02/MicrobeEvent_02.h"
#include <glm/fwd.hpp>

void CellMove::action()
{
	if (!requestEnergy()) {
		return;
	}

	if (!_core) {
		return;
	}

	if (glm::length(vectorMove) == 0.0f) {
		return;
	}

	_stockEnergy -= _consumption;

	glm::vec3 vector = glm::normalize(vectorMove);
	vector *= 0.025f;

#if _DEBUG
	vector *= 2.5f;
#endif

	vector.z = 0.0f;
	_core->_physic->setVectorPhysic(vector);

	vectorMove.x = 0.0f;
	vectorMove.y = 0.0f;
	vectorMove.z = 0.0f;
}

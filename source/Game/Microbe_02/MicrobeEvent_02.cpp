
#include "Microbe_02.h"

void Microbe_02::applyEvents()
{
	for (auto& event : _events) {
		switch (event)
		{
		case Microbe_02::MOVE:  {
			moveEvent();
		} break;
		default:
			break;
		}
	}
}

void Microbe_02::moveEvent() {
	glm::vec3 vector(0.2f, 0.1f, 0.0f);
	_physic->setVectorPhysic(vector);
}

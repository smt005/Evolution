
#include "CellBrain.h"
#include "CellEnergy.h"
#include "Microbe_02/Microbe_02.h"
#include "Microbe_02/MicrobeEvent_02.h"
#include "Microbe_02/Food_02.h"
#include <glm/mat4x4.hpp>

glm::vec3 CellBrain::targetPos = glm::vec3(0.0f, 0.0f, 1.0f);

void CellBrain::init() {

}

void CellBrain::action()
{
	if (!requestEnergy()) {
		return;
	}

	if (!_core) {
		return;
	}

	if (_core->cellEnergy->_stockEnergy >= _core->cellEnergy->_maxStockEnergy) {
		return;
	}

	glm::vec3 vectorMove = vectorToFood();

	if (glm::length(vectorMove) == 0.0f) {
		return;
	}

	DataMoveEvent* data = new DataMoveEvent();
	data->move = vectorMove;
	Microbe_02::Event eventMove(data);

	_core->addEvent(eventMove);
}
glm::vec3 CellBrain::vectorToFood()
{
	glm::vec3 pos = _core->_physic->getPosPhysic();
	float nearestDist = FLT_MAX;
	Food_02Ptr nearestFood;

	for (auto& food : Food_02::getItems())
	{
		if (!food->_live)  continue;

		glm::vec3 vDist = pos - food->_physic->getPosPhysic();
		float dist = glm::length(vDist);

		if (dist <= nearestDist) {
			nearestDist = dist;
			nearestFood = food;
		}
	}

	glm::vec3 vecrorMove(0.0f, 0.0f, 0.0f);

	if (nearestFood) {
		vecrorMove = nearestFood->_physic->getPosPhysic() - pos;
		vecrorMove.z = 0.0f;
	}
	return vecrorMove;
}

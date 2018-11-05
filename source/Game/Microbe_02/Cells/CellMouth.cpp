
#include "CellMouth.h"
#include "Microbe_02/MicrobeEvent_02.h"
#include "Microbe_02/Food_02.h"

void CellMouth::action()
{
	if (!requestEnergy()) {
		return;
	}

	if (!_core) {
		return;
	}

	Food_02Ptr food = contactToFood();

	_stockEnergy -= _consumption;

	if (food) {
		DataEatEvent* data = new DataEatEvent();
		data->microbe = _core;
		data->food = food;
		Microbe_02::Event eventEat(data);

		_core->addEvent(eventEat);
	}
}

Food_02Ptr CellMouth::contactToFood()
{
	glm::vec3 pos = _core->_physic->getPosPhysic();

	for (auto& food : Food_02::getItems())
	{
		if (!food->_live)  continue;

		glm::vec3 vDist = pos - food->_physic->getPosPhysic();
		float dist = glm::length(vDist);

		if (dist <= (_core->_physic->getRadiusPhysic() + food->_physic->getRadiusPhysic())) {
			return food;
		}
	}
}

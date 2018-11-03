
#include "CellBrain.h"
#include "Microbe_02/Microbe_02.h"
#include "Microbe_02/MicrobeEvent_02.h"
#include <glm/mat4x4.hpp>

glm::vec3 CellBrain::targetPos = glm::vec3(0.0f, 0.0f, 1.0f);

void CellBrain::init() {

}

void CellBrain::action()
{
	if (!_core) {
		return;
	}

	glm::mat4x4 mat = _core->getMatrix();
	glm::vec3 pos(mat[3][0], mat[3][1], 1.0f);
	glm::vec3 vectorMove = targetPos - pos;
	vectorMove.z = 0.0f;

	DataMoveEvent* data = new DataMoveEvent();
	data->move = vectorMove;
	Microbe_02::Event eventMove(data);

	_core->addEvent(eventMove);
}

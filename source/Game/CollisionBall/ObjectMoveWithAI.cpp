#include "ObjectMoveWithAI.h"
#include "Common/Help.h"

glm::vec3 ObjectMoveWithAI::targetPos = glm::vec3(10.0f, 10.0f, 1.0f);

ObjectMoveWithAI::ObjectMoveWithAI()
{
	_speedFactor = help::random_f(0.05f, 0.2f);
}

void ObjectMoveWithAI::action()
{
	glm::vec3 distVector = targetPos - getPos();
	if (distVector.length() < 3.0f) {
		return;
	}

	distVector = glm::normalize(distVector) * _speedFactor;
	distVector.z = 0.0f;
	vectorMove = distVector;
}

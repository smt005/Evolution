#pragma once

#include "ObjectMove.h"
#include <glm/vec3.hpp>

class ObjectMoveWithAI : public ObjectMove
{
public:
	ObjectMoveWithAI();
	virtual void action() override;

public:
	static glm::vec3 targetPos;

private:
	float _speedFactor = 0.1f;
};
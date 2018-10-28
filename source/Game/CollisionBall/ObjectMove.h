#pragma once

#include "Object/Object.h"
#include <glm/vec3.hpp>

class ObjectMove : public Object
{
public:
	inline float getRadius() { return 1.0f; }
	inline float getMass() { return 1.0f; }

	bool colliding(ObjectMove& ball);
	void resolveCollision(ObjectMove& ball);

public:
	glm::vec3 vectorMove;
};


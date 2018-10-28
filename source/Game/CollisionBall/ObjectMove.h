#pragma once

#include "Object/Object.h"
#include <glm/vec3.hpp>

class ObjectMove : public Object
{
public:
	ObjectMove();
	~ObjectMove();

public:
	glm::vec3 vectorMove;

};


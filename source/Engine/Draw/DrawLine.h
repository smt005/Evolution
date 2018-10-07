
#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Object/Color.h"

#include "Object/Line.h"

namespace draw
{

class DrawLine
{
public:
	static void prepare();
	static void draw(const Line& line);
};

}
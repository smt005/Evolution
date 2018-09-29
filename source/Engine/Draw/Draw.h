
#pragma once

#include <glm/glm.hpp>
#include "glm/mat4x4.hpp"

class Mesh;

class Draw
{
public:
	static void setClearColor(const float r, const float g, const float b, const float a);
	static const float * const getClearColor();

	static void clearColor();
	static void prepare();

	static void drawBackround();
	static void drawTriangle();
	static void draw(Mesh& mesh, glm::mat4x4& matrix);

	static void drawTriangleExample();
};
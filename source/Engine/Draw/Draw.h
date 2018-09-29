
#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

class Mesh;
class Model;
class Object;
class Map;

class Draw
{
public:
	static void setClearColor(const float r, const float g, const float b, const float a);
	static const float * const getClearColor();

	static void clearColor();
	static void prepare();

	static void drawTriangleExample();

	static void draw(Mesh& mesh);
	static void draw(Model& model);
	static void draw(Object& object);
	static void draw(Map& map);
};
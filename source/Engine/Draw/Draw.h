
#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include "Microbe_02/Microbe_02.h"
#include "Common/ItemsClass.h"

class Mesh;
class Model;
class Object;
class Map;
class Triangle;

class Draw
{
public:
	static void setClearColor(const float r, const float g, const float b, const float a);
	static const float * const getClearColor();
	static void setMatrixToShader(const glm::mat4x4& matrix);

	static void clearColor();
	static void viewport();
	static void prepare();

	static void draw(Mesh& mesh);
	static void draw(Model& model);
	static void draw(Object& object);
	static void draw(Map& map);
	static void draw(const Triangle& triangle);

	template <class ContainerT>
	static void draw() {
		for (auto& item : Microbe_02::getItems()) {
			if (item) {
				setMatrixToShader(item->getMatrix());
				ModelPtr model = item->getModel();
				draw(*model);
			}
		}
	}
};

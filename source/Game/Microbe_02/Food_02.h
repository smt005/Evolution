#pragma once

#include "Physic/PhysicCircle2D.h"
#include "Object/Triangle.h"
#include "Common/ItemsClass.h"

class Microbe_02;
class Food_02;
typedef std::shared_ptr<Food_02> Food_02Ptr;

class Food_02 final : public ItemsClass <Food_02>
{
	friend Microbe_02;
public:
	Food_02();
	~Food_02();

	void init(const glm::vec3& pos);
	void update() override;
	glm::mat4x4 getMatrix() override;
	TrianglePtr getModel() {
		return _triangle;
	}
	void kill() {
		_live = nullptr;
	}

public:
	static void generate(const unsigned int count);

public:
	PhysicCircle2DPtr	_physic;
	TrianglePtr			_triangle;
	std::shared_ptr<float> _live;
};

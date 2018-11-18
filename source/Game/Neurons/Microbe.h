#pragma once

#include "Object/Triangle.h"
#include "Physic/PhysicCircle2D.h"
#include "Object/Identify.h"
#include "Common/ItemsClass.h"
#include <memory>
#include <vector>

class Microbe;
typedef std::shared_ptr<Microbe> MicrobePtr;

class Microbe final : public ItemsClass<Microbe>, public UniqueId
{
public:
	Microbe();
	~Microbe();
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
	PhysicCircle2DPtr	_physic;
	TrianglePtr			_triangle;
	std::shared_ptr<float> _live;

public:
	static void generate(const unsigned int count);
};

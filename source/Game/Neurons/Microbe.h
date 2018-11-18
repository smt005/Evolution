#pragma once

#include "Object/Triangle.h"
#include "Physic/PhysicCircle2D.h"
#include "Object/Identify.h"
#include "Common/ItemsClass.h"
#include <memory>
#include <vector>

class Microbe;
typedef std::shared_ptr<Microbe> MicrobePtr;
class CellMove;
typedef std::shared_ptr<CellMove> CellMovePtr;
class CellBrain;
typedef std::shared_ptr<CellBrain> CellBrainPtr;

class Microbe final : public ItemsClass<Microbe>, public UniqueId
{
	friend CellBrain;
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

	std::vector<CellMovePtr> _cellsMove;
	std::vector<CellBrainPtr> _cellsBrain;

public:
	static void generate(const unsigned int count);
};

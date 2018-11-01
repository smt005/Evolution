#pragma once

#include "Object/Triangle.h"
#include "Physic/PhysicCircle2D.h"
#include "Object/Identify.h"
#include "Object/Shape.h"
#include <glm/vec3.hpp>
#include <memory>

class CellEnergy;
typedef std::shared_ptr<CellEnergy> CellEnergyPtr;
class CellMove;
typedef std::shared_ptr<CellMove> CellMovePtr;
class CellMouth;
typedef std::shared_ptr<CellMouth> CellMouthPtr;
class CellBrain;
typedef std::shared_ptr<CellBrain> CellBrainPtr;

class Microbe_02 final : public UniqueId
{
public:
	Microbe_02();
	~Microbe_02();
	void init(const glm::vec3& pos);
	void update();

public:
	CellEnergyPtr	cellEnergy;
	CellMovePtr		cellMove;
	CellMouthPtr	cellMouth;
	CellBrainPtr	cellBrain;

	PhysicCircle2DPtr	physic;
	//TrianglePtr			triangle;
	ShapePtr			shape;
};

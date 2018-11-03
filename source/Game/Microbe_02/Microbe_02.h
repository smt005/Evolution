#pragma once

#include "Object/Triangle.h"
#include "Physic/PhysicCircle2D.h"
#include "Object/Identify.h"
#include "Object/Model.h"
#include "Common/ItemsClass.h"
#include <memory>
#include <vector>

class Microbe_02;
typedef std::shared_ptr<Microbe_02> Microbe_02Ptr;
class CellEnergy;
typedef std::shared_ptr<CellEnergy> CellEnergyPtr;
class CellMove;
typedef std::shared_ptr<CellMove> CellMovePtr;
class CellMouth;
typedef std::shared_ptr<CellMouth> CellMouthPtr;
class CellBrain;
typedef std::shared_ptr<CellBrain> CellBrainPtr;

class Microbe_02 final : public ItemsClass <Microbe_02>, public UniqueId
{
public:
	Microbe_02();
	~Microbe_02();
	void init(const glm::vec3& pos);
	void update();
	glm::mat4x4 getMatrix() override;
	ModelPtr getModel() override;

public:
	CellEnergyPtr	cellEnergy;
	CellMovePtr		cellMove;
	CellMouthPtr	cellMouth;
	CellBrainPtr	cellBrain;

private:
	PhysicCircle2DPtr	_physic;
	ModelPtr			_model;

public:
	static void generate(const unsigned int count);
};

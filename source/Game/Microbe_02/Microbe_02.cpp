#include "Microbe_02.h"
#include "Cells/Cell.h"
#include "Cells/CellEnergy.h"
#include "Cells/CellMove.h"
#include "Cells/CellMouth.h"
#include "Cells/CellBrain.h"

Microbe_02::Microbe_02() {
}

Microbe_02::~Microbe_02() {
}

void Microbe_02::init(const glm::vec3 & pos)
{
	cellEnergy = CellEnergyPtr(new CellEnergy());
	cellMove = CellMovePtr(new CellMove());
	cellMouth = CellMouthPtr(new CellMouth());
	cellBrain = CellBrainPtr(new CellBrain());

	physic = PhysicCircle2DPtr(new PhysicCircle2D(true));
	//triangle = TrianglePtr(new Triangle());
	shape = Shape::getByName("Sphere_01");
}

void Microbe_02::update()
{
}

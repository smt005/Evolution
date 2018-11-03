#include "Microbe_02.h"
#include "Cells/Cell.h"
#include "Cells/CellEnergy.h"
#include "Cells/CellMove.h"
#include "Cells/CellMouth.h"
#include "Cells/CellBrain.h"
#include "Common/Help.h"

Microbe_02::Microbe_02() {
}

Microbe_02::~Microbe_02() {
}

void Microbe_02::init(const glm::vec3 & pos)
{
	cellEnergy = CellEnergyPtr(new CellEnergy(this));
	cellMove = CellMovePtr(new CellMove(this));
	cellMouth = CellMouthPtr(new CellMouth(this));
	cellBrain = CellBrainPtr(new CellBrain(this));

	_physic = PhysicCircle2D::addPhysic();
	_physic->setPosPhysic(pos);

	_model = Model::getByName("Sphere_01");
}

void Microbe_02::update() {
	applyEvents();

	cellEnergy->action();
	cellMove->action();
	cellMouth->action();
	cellBrain->action();
}

glm::mat4x4 Microbe_02::getMatrix()
{
	if (!_physic) {
		return glm::mat4x4();
	}

	glm::mat4x4 matrix(1.0f);
	glm::vec3 pos = _physic->getPosPhysic();
	matrix[3][0] = pos.x;
	matrix[3][1] = pos.y;
	matrix[3][2] = pos.z;

	return matrix;
}

ModelPtr Microbe_02::getModel() {
	return _model;
}

// static

void Microbe_02::generate(const unsigned int count)
{
	clear();

	for (unsigned int i = 0; i < count; ++i) {
		glm::vec3 pos(help::random_f(-25.0f, 25.0f), help::random_f(-25.0f, 25.0f), 1.0f);
		Microbe_02Ptr microbe = addItem();
		microbe->init(pos);
	}
}

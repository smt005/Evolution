#include "Microbe_02.h"
#include "Cells/Cell.h"
#include "Cells/CellTouch.h"
#include "Cells/CellEnergy.h"
#include "Cells/CellMove.h"
#include "Cells/CellMouth.h"
#include "Cells/CellBrain.h"
#include "Common/Help.h"

Microbe_02::Microbe_02()
	: _live(std::shared_ptr<float>(new float(1.0f))) {
}

Microbe_02::~Microbe_02() {
}

void Microbe_02::init(const glm::vec3 & pos)
{
	cellTouch = CellTouchPtr(new CellTouch(this));
	cellEnergy = CellEnergyPtr(new CellEnergy(this));
	cellMove = CellMovePtr(new CellMove(this));
	cellMouth = CellMouthPtr(new CellMouth(this));
	cellBrain = CellBrainPtr(new CellBrain(this));

	float radius = help::random_f(0.125f, 1.0f);
	_physic = PhysicCircle2D::addPhysic();
	_physic->setPosPhysic(pos);
	_physic->setRadiusPhysic(radius);

	float area = 1.0f;	// help::areaCircle(radius) / M_PI * 0.9f;
	_physic->setMassPhysic(area);

	_triangle = Triangle::generateTriangle(radius);
	_triangle->setTexture("Textures/Cell_light.png");
	_triangle->setColor( {0.0f, 1.0f, 1.0f, 1.0f} );
}

void Microbe_02::update() {
	applyEvents();

	cellTouch->action();
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

// static

void Microbe_02::generate(const unsigned int count)
{
	clear();

	bool typeBrain = true;

	for (unsigned int i = 0; i < count; ++i) {
		glm::vec3 pos(help::random_f(-25.0f, 25.0f), help::random_f(-25.0f, 25.0f), 1.0f);
		Microbe_02Ptr microbe = addItem();
		microbe->init(pos);

		if (typeBrain) {
			microbe->cellBrain->brain = new Brain();
			NeuronTest* neuron = new NeuronTest();
			microbe->cellBrain->brain->add(neuron);

			microbe->cellMove->inNeuron = neuron;
			microbe->cellMove->state = true;
		}
	}
}

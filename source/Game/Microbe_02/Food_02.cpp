#include "Food_02.h"
#include "Common/Help.h"

Food_02::Food_02()
	: _live(std::shared_ptr<float>(new float(1.0f)))
{
}

Food_02::~Food_02()
{
}

void Food_02::init(const glm::vec3 & pos)
{
	float radius = help::random_f(0.125f, 0.5f);
	_physic = PhysicCircle2D::addPhysic();
	_physic->setPosPhysic(pos);
	_physic->setRadiusPhysic(radius);

	float area = 1.0f;	// help::areaCircle(radius) / M_PI * 0.9f;
	_physic->setMassPhysic(area);

	_triangle = Triangle::generateTriangle(radius);
	_triangle->setTexture("Textures/Cell_light.png");
	_triangle->setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
}

void Food_02::update() {
	if (!_live) {
		_triangle->setColor(Color::BLACK);
	}
}

glm::mat4x4 Food_02::getMatrix()
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

void Food_02::generate(const unsigned int count)
{
	clear();

	for (unsigned int i = 0; i < count; ++i) {
		glm::vec3 pos(help::random_f(-25.0f, 25.0f), help::random_f(-25.0f, 25.0f), 1.0f);
		Food_02Ptr microbe = addItem();
		microbe->init(pos);
	}
}

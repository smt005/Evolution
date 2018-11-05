
#include "PhysicCircle2D.h"
#include <glm/glm.hpp>

std::vector<PhysicCircle2DPtr> PhysicCircle2D::_physicObjects;
size_t PhysicCircle2D::_countPhysicIteration = 10;
float PhysicCircle2D::_frictionCoefficient = 0.9965f;

PhysicCircle2D::PhysicCircle2D()
	: _posPhysic(glm::vec3(0.0f, 0.0f, 0.0f))
	, _vecPhysic(glm::vec3(0.0f, 0.0f, 0.0f))
	, _massPhysic(1.0f)
	, _radiusPhysic(1.0f)
{
	_radiusPhysic = 1.0f;
}

PhysicCircle2D::PhysicCircle2D(bool addToObjects)
	: _posPhysic(glm::vec3(0.0f, 0.0f, 0.0f))
	, _vecPhysic(glm::vec3(0.0f, 0.0f, 0.0f))
	, _massPhysic(1.0f)
	, _radiusPhysic(1.0f)
{
	if (addToObjects) {
		PhysicCircle2DPtr objectPtr = PhysicCircle2DPtr(this);
		_physicObjects.push_back(objectPtr);
	}
}

PhysicCircle2D::PhysicCircle2D(const float * const pos) {
	if (pos) {
		_posPhysic.x = pos[0]; _posPhysic.y = pos[1]; _posPhysic.z = pos[2];
	}
}

PhysicCircle2D::PhysicCircle2D(const glm::vec3 & pos) 
	: _posPhysic(pos)
{
}

PhysicCircle2D::~PhysicCircle2D() {
}


bool PhysicCircle2D::colliding(PhysicCircle2D& ball)
{
	float xd = _posPhysic.x - ball._posPhysic.x;
	float yd = _posPhysic.y - ball._posPhysic.y;

	float sumRadius = _radiusPhysic + ball._radiusPhysic;
	float sqrRadius = sumRadius * sumRadius;

	float distSqr = (xd * xd) + (yd * yd);

	if (distSqr <= sqrRadius) {
		return true;
	}

	return false;
}

void PhysicCircle2D::resolveCollision(PhysicCircle2D& ball)
{
	// get the mtd
	glm::vec3 delta = ball._posPhysic - _posPhysic;
	float d = delta.length();
	glm::vec3 mtd = delta * (((_radiusPhysic + ball._radiusPhysic) - d) / d);

	// resolve intersection --
	// inverse mass quantities
	float im1 = 1.0f / _massPhysic;
	float im2 = 1.0f / ball._massPhysic;

	// push-pull them apart based off their mass
	_posPhysic = _posPhysic + (mtd * (im1 / (im1 + im2)));
	_posPhysic = _posPhysic - (mtd * (im2 / (im1 + im2)));

	// impact speed
	glm::vec3 v = _vecPhysic - ball._vecPhysic;
	float vn = glm::dot(v, glm::normalize(mtd));

	// sphere intersecting but moving away from each other already
	if (vn > 0.0f) return;

	// collision impulse
	float Constants_restitution = 1.0f;
	float i = (-(1.0f + Constants_restitution) * vn) / (im1 + im2);
	glm::vec3 impulse = mtd * i;

	// change in momentum
	_vecPhysic = _vecPhysic + impulse * im1;
	ball._vecPhysic = ball._vecPhysic - impulse * im2;
}

// static

void PhysicCircle2D::updatePhysic()
{
	size_t count = _physicObjects.size();

	for (int iteration = 0; iteration < _countPhysicIteration; ++iteration) {
		for (int i = 0; i < count; i++)
		{
			PhysicCircle2D& object = *_physicObjects[i];

			for (int j = i + 1; j < count; j++) {
				if (object.colliding(*_physicObjects[j])) {
					object.resolveCollision(*_physicObjects[j]);
				}
			}
		}
	}

	for (PhysicCircle2DPtr& object : _physicObjects) {
		object->_vecPhysic *= _frictionCoefficient;
		object->move();
	}
}

PhysicCircle2DPtr PhysicCircle2D::addPhysic() {
	PhysicCircle2DPtr objectPtr = PhysicCircle2DPtr(new PhysicCircle2D());
	_physicObjects.push_back(objectPtr);
	return objectPtr;
}

PhysicCircle2DPtr PhysicCircle2D::addPhysic(const float * const pos) {
	PhysicCircle2DPtr objectPtr = PhysicCircle2DPtr(new PhysicCircle2D(pos));
	_physicObjects.push_back(objectPtr);
	return objectPtr;
}

PhysicCircle2DPtr PhysicCircle2D::addPhysic(const glm::vec3 & pos) {
	PhysicCircle2DPtr objectPtr = PhysicCircle2DPtr(new PhysicCircle2D(pos));
	_physicObjects.push_back(objectPtr);
	return objectPtr;
}

void PhysicCircle2D::removePhysic(PhysicCircle2DPtr object)
{
}

void PhysicCircle2D::removePhysic(const long unsigned int id)
{
}

void PhysicCircle2D::clearPhysic() {
	_physicObjects.clear();
}

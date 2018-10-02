
#include "Microbe.h"
#include "../Engine/Object/ShapeTriangles.h"
#include "Common/Help.h"

ShapeTrianglesPtr Microbe::shapePtrStatic = nullptr;
std::vector<MicrobePtr> Microbe::_microbes;

Microbe::Microbe() {
	create();
}


Microbe::Microbe(const glm::vec3& pos) {
	create();

	_matrix[3][0] = pos.x;
	_matrix[3][1] = pos.y;
	_matrix[3][2] = pos.z;
}

void Microbe::create()
{
	if (!shapePtrStatic)
	{
		ShapeTriangles* shape = new ShapeTriangles();
		ShapeTriangles::makeTriangle(*shape);

		shapePtrStatic = ShapeTrianglesPtr(shape);
	}

	_shapePtr = shapePtrStatic;
}

Microbe::~Microbe()
{

}

ShapeTriangles& Microbe::shape()
{
	if (!_shapePtr) {
		create();
	}
	return _shapePtr->getSelf();
}

void Microbe::setMatrix(const float *matrix)
{
	_matrix[0][0] = matrix[0];
	_matrix[0][1] = matrix[1];
	_matrix[0][2] = matrix[2];
	_matrix[0][3] = matrix[3];

	_matrix[1][0] = matrix[4];
	_matrix[1][1] = matrix[5];
	_matrix[1][2] = matrix[6];
	_matrix[1][3] = matrix[7];

	_matrix[2][0] = matrix[8];
	_matrix[2][1] = matrix[9];
	_matrix[2][2] = matrix[10];
	_matrix[2][3] = matrix[11];

	_matrix[3][0] = matrix[12];
	_matrix[3][1] = matrix[13];
	_matrix[3][2] = matrix[14];
	_matrix[3][3] = matrix[15];
}

void Microbe::action()
{
	if (!_live) return;

	foundTarget();

	if (_target) {
		glm::vec3 selfPos = getPos();
		glm::vec3 targetPos = _target->getPos();
		_vector = targetPos - selfPos;
		_vector.z = 0.0f;

		if (glm::length(_vector) != 0.0f) {
			_vector = glm::normalize(_vector);
		}
	}

	move();
	attack();
}

void Microbe::move()
{
	if (glm::length(_vector) == 0.0f) return;

	glm::vec3 moveVector = _vector * 0.001f; //_speed;

	_matrix[3][0] += moveVector.x;
	_matrix[3][1] += moveVector.y;
}

void Microbe::attack()
{
	if (_target) {
		glm::vec3 selfPos = getPos();
		glm::vec3 targetPos = _target->getPos();
		_vector = targetPos - selfPos;

		float dist = glm::length(_vector);
		if (dist < 0.1f) {
			_target->_live = false;
			_target->_matrix[3][2] = -1.0f;
			_target = nullptr;
		}
	}
}

void Microbe::foundTarget()
{
	if (_target) return;

	if (_target &&  !_target->_live) {
		_target = nullptr;
	}

	MicrobePtr nearest;

	int id = getIdAddres();
	glm::vec3 selfPos = getPos();
	float nearestDist = 1000000.0f;
	glm::vec3 vectorDist;

	for (auto& microbe : _microbes) {
		if (microbe) {
			if (id == microbe->getIdAddres())
			{
				continue;
			}

			if (microbe->_live = false) continue;

			glm::vec3 pos = microbe->getPos();
			vectorDist = pos - selfPos;
			float dist = glm::length(vectorDist);

			if (dist < nearestDist) {
				nearestDist = dist;
				nearest = microbe;
			}
		}
	}

	_target = nearest;
}

// STATIC 

void Microbe::generateMicrobes(const size_t count)
{
	_microbes.clear();
	_microbes.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		glm::vec3 pos;
		pos.x = help::random_f(-40.0f, 40.0f);
		pos.y = help::random_f(-40.0f, 40.0f);
		pos.z = help::random_f(1.0f, 1.5f);

		Microbe* microbe = new Microbe(pos);
		_microbes.push_back(MicrobePtr(microbe));
	}
}

void Microbe::update()
{
	for (auto& microbe : _microbes) {
		if (microbe) {
			microbe->action();
		}
	}
}

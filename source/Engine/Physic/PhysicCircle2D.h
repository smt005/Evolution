#pragma once

#include <memory>
#include <vector>
#include <glm/vec3.hpp>
#include "Object/Identify.h"

class PhysicCircle2D;
typedef std::shared_ptr<PhysicCircle2D> PhysicCircle2DPtr;

class PhysicCircle2D : public UniqueId
{
public:
	PhysicCircle2D();
	PhysicCircle2D(bool addToObjects);
	PhysicCircle2D(const float* const pos);
	PhysicCircle2D(const glm::vec3& pos);
	virtual ~PhysicCircle2D();

	inline void setPosPhysic(const float* const pos)		{ _posPhysic.x = pos[0]; _posPhysic.y = pos[1]; _posPhysic.z = pos[2]; }
	inline void setPosPhysic(const glm::vec3& pos)		{ _posPhysic = pos; }
	inline void setVectorPhysic(const float* const vec)	{ _vecPhysic.x = vec[0]; _vecPhysic.y = vec[1]; _vecPhysic.z = vec[2]; }
	inline void setVectorPhysic(const glm::vec3& vec)		{ _vecPhysic = vec; }
	inline void setMassPhysic(const float mass)			{ _massPhysic = mass; }
	inline void setRadiusPhysic(const float radius)		{ _radiusPhysic = radius; }

	inline const glm::vec3& getPosPhysic()		{ return _posPhysic; }
	inline const glm::vec3& getVectorPhysic()		{ return _vecPhysic; }
	inline float getMassPhysic(const float mass)		{ return _massPhysic; }
	inline float getRadiusPhysic(const float radius)	{ return _radiusPhysic; }

private:
	bool colliding(PhysicCircle2D& circle);
	void resolveCollision(PhysicCircle2D& circle);
	inline void move() { _posPhysic += _vecPhysic; }

public:
	static void updatePhysic();
	static PhysicCircle2DPtr addPhysic();
	static PhysicCircle2DPtr addPhysic(const float* const pos);
	static PhysicCircle2DPtr addPhysic(const glm::vec3& pos);
	static void removePhysic(PhysicCircle2DPtr object);
	static void removePhysic(const long unsigned int id);
	static void clearPhysic();

private:
	glm::vec3 _posPhysic;
	glm::vec3 _vecPhysic;
	float _massPhysic;
	float _radiusPhysic;

private:
	static std::vector<PhysicCircle2DPtr> _physicObjects;
	static size_t _countPhysicIteration;
	static float _frictionCoefficient;
};

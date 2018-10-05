#pragma once

#include <string>
#include <memory>
#include <vector>

#include "glm/mat4x4.hpp"
#include <glm/gtc/type_ptr.hpp>

class ShapeTriangles;
typedef std::shared_ptr<ShapeTriangles> ShapeTrianglesPtr;

class Microbe;
typedef std::shared_ptr<Microbe> MicrobePtr;

class Microbe
{
public:
	Microbe();
	Microbe(const glm::vec3& pos);
	~Microbe();

	ShapeTriangles& shape();
	inline int getIdAddres() { return reinterpret_cast<int>(this); }
	inline ShapeTrianglesPtr shapePtr() { return _shapePtr; }
	inline void setName(const std::string& name) { _name = name; }

	inline const std::string& name() { return _name; }
	inline const glm::mat4x4& getMatrix() { return _matrix; }
	inline const float* matrixFloat() { return glm::value_ptr(_matrix); }
	inline glm::vec3 getPos() { return glm::vec3(_matrix[3][0], _matrix[3][1], _matrix[3][2]); }
	inline void setMatrix(const glm::mat4x4 &matrix) { _matrix = matrix; }
	void setMatrix(const float *matrix);
	inline glm::vec3 getScale() { return _scale; }

	void action();
	void move();
	void moveNext();
	bool moveCheck();
	bool collisionCheck();
	void attack();
	void foundTarget();
	//inline bool isHimSelf(Microbe* microbe) { return microbe == this ? true : false; }

public:
	static std::vector<MicrobePtr>& microbes() { return _microbes; }
	static void generateMicrobes(const size_t count);
	static void update();
	static void clear() { _microbes.clear(); }

private:
	void create();

private:
	std::string _name;
	glm::mat4x4 _matrix = glm::mat4x4(1.0f);
	ShapeTrianglesPtr _shapePtr;
	float _mass = 1.0f;
	float _speed = 0.01f;

	MicrobePtr _target;
	glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 _vector = glm::vec3(1.0f, 0.0f, 0.0f);
	bool _live = true;

	glm::vec3 _nextPos;

private:
	static ShapeTrianglesPtr shapePtrStatic;
	static std::vector<MicrobePtr> _microbes;
};
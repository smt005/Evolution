
#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "Color.h"

using namespace draw;

class DrawLine
{
public:
	DrawLine() {
		_data[0] = 0.0f;
		_data[1] = 0.0f;
		_data[2] = 0.0f;

		_data[3] = 0.0f;
		_data[4] = 0.0f;
		_data[5] = 1.0f;
	}

	DrawLine(const float* const posFirst, const float* const posSecond) { set(posFirst, posSecond); }
	DrawLine(const glm::vec3& posFirst, const glm::vec3& posSecond) { set(posFirst, posSecond); }
	void draw();

	inline void set(const float* const posFirst, const float* const posSecond) {
		_data[0] = posFirst[0];
		_data[1] = posFirst[1];
		_data[2] = posFirst[2];

		_data[3] = posSecond[0];
		_data[4] = posSecond[1];
		_data[5] = posSecond[2];
	}

	inline void set(const glm::vec3& posFirst, const glm::vec3& posSecond) {
		_data[0] = posFirst.x;
		_data[1] = posFirst.y;
		_data[2] = posFirst.z;

		_data[3] = posSecond.x;
		_data[4] = posSecond.y;
		_data[5] = posSecond.z;
	}

	inline void setPosFirst(const float* const posFirst) {
		_data[0] = posFirst[0];
		_data[1] = posFirst[1];
		_data[2] = posFirst[2];
	}

	inline void setPosSecond(const float* const posSecond) {
		_data[3] = posSecond[0];
		_data[4] = posSecond[1];
		_data[5] = posSecond[2];
	}

	inline void setPosFirst(const glm::vec3& posFirst) {
		_data[0] = posFirst.x;
		_data[1] = posFirst.y;
		_data[2] = posFirst.z;
	}

	inline void setPosSecond(const glm::vec3& posSecond) {
		_data[3] = posSecond.x;
		_data[4] = posSecond.y;
		_data[5] = posSecond.z;
	}

	inline glm::vec3 getPosFirst()	{ return glm::vec3(_data[0], _data[1], _data[2]); }
	inline glm::vec3 getPosSecond()	{ return glm::vec3(_data[3], _data[4], _data[5]); }

	inline void setColor(const Color& color) { _color = color; }

public:
	static void prepare();

private:
	float _data[6];
	Color _color = Color(Color::WHITE);
};

// TODO: прототип - неоптимизированно

class DrawGrid
{
public:
	DrawGrid();
	void draw();

	inline void set(const int countX, const int countY, const float step) {
		_countX = countX;
		_countY = countY;
		_step = step;
	}

	inline void setColorX(const Color& color) { _colorX = color; }
	inline void setColorY(const Color& color) { _colorY = color; }
	inline void setColorZ(const Color& color) { _colorZ = color; }

public:
	inline static void prepare() { DrawLine::prepare(); }

private:
	int _countX = 10;
	int _countY = 10;
	float _step = 1.0f;

	Color _colorX;
	Color _colorY;
	Color _colorZ;
};

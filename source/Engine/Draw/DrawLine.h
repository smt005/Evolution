
#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Color.h"

using namespace draw;

class DrawLine
{
public:
	DrawLine() { }

	DrawLine(const float* const posFirst, const float* const posSecond) { set(posFirst, posSecond); }
	DrawLine(const glm::vec3& posFirst, const glm::vec3& posSecond) { set(posFirst, posSecond); }
	
	inline void setColor(const Color& color) { _color = color; }
	inline void set(const glm::vec3& posFirst, const glm::vec3& posSecond) {
		set(glm::value_ptr(posFirst), glm::value_ptr(posSecond));
	}
	
	inline float getLineWidth() { return _lineWidth; }
	inline void setLineWidth(const float lineWidth) { _lineWidth = lineWidth; }

	void set(const float* const posFirst, const float* const posSecond);
	void draw();

public:
	static void prepare();

private:
	int _count = 0;	// 4 => 2(линии) * 2(точки в одной линии) * 3 (3 компоненты - xyz)
	float* _data;
	float _lineWidth = 1.0f;
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

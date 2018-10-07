#pragma once

#include <memory>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

#include "Color.h"
#include "Point.h"
#include "Position.h"

class Greed;

class Line
{
	friend Greed;

public:
	struct Point {
		float data[3];
		Point() {
			data[0] = 0.0f;
			data[1] = 0.0f;
			data[2] = 0.0f;
		}
	};

	enum
	{
		NONE,
		LINE,
		LOOP,
		STRIP
	};

public:
	Line()
		: color(Color::RED)
		, _lineWidth(1.0f)
	{}
	Line(const float* const points, const unsigned int count, const unsigned short int type = LINE)
		: color(Color::RED)
		, _lineWidth(1.0f)
	{
		set(points, count, type);
	}

	~Line();

	template <class PointT>
	void set(const PointT* const points, const unsigned int count, const unsigned short int type = LINE) {
		if (points == nullptr || count < 2) {
			return;
		}

		_count = count;

		_points = new Point[_count];
		memcpy(_points, points, sizeof(Point) * _count);

		_type = type;
	}

	inline void setType(const unsigned short int type) { _type = type; }
	inline void setLineWidth(const float lineWidth) { _lineWidth = lineWidth; }

	inline float* getData() const { return (float*)_points; }
	inline unsigned int getCount() const { return _count; }
	inline unsigned short int getType() const { return _type; }
	inline float getLineWidth() const { return _lineWidth; }

	Line& operator=(const Line& line);

public:
	Color color;	// �������� TODO:

private:
	unsigned short int _type;	// GL_LINES 0x0001, GL_LINE_LOOP 0x0002, GL_LINE_STRIP 0x0003
	float _lineWidth;
	unsigned int _count;
	Point* _points;
};


class Greed : public Position
{
public:
	Greed()	{ }

	Greed(const float width, const float step = 1.0f) {
		set(width, step);
	}

	void set(const float width, const float step = 1.0f);

private:
	void generateLines(Line& line, const float width, const float step, const bool planeX);

public:
	Line lineX;
	Line lineY;
	Line lineZ;

	Line heavyLineX;
	Line heavyLineY;
	Line heavyLineZ;
};
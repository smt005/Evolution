#pragma once

#include <memory>

#include "Color.h"
#include "Point.h"

class Line
{
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
	explicit Line(const float* const points, const unsigned int count = 1, const unsigned short int type = LINE);

	~Line();

	inline void setType(const unsigned short int type) { _type = type; }
	inline void setLineWidth(const float lineWidth) { _lineWidth = lineWidth; }

	inline float* getData() const { return (float*)_points; }
	inline unsigned int getCount() const { return _count; }
	inline unsigned short int getType() const { return _type; }
	inline float getLineWidth() const { return _lineWidth; }

	Line& operator=(const Line& line);

public:
	Color color;	// Временно TODO:

private:
	unsigned short int _type;	// GL_LINES 0x0001, GL_LINE_LOOP 0x0002, GL_LINE_STRIP 0x0003
	float _lineWidth;
	unsigned int _count;
	Point* _points;

	//unsigned int _countColor;
	//Color* _colors;
};

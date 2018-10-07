
#include "Line.h"

Line::Line(const float* const points, const unsigned int count, const unsigned short int type)
	: color(Color::RED)
	, _lineWidth(1.0f)
{
	if (points == 0 || count == 0) {
		return;
	}

	_count = count == 1 ? 2 : count;

	_points = new Point[_count];
	memcpy(_points, points, sizeof(Point) * _count);

	_type = type;
}

Line::~Line()
{
	if (_points) {
		delete[] _points;
	}

	/*if (_colors) {
		delete[] _colors;
	}*/
}

Line& Line::operator=(const Line& line) {
	if (line._points && line._count) {
		_count = line._count;
		memcpy(_points, line._points, sizeof(Point) * _count);
		_type = line._type;
	}
	else {
		return *this;
	}

	/*if (line._colors && line._countColor) {
		_countColor = line._countColor;
		memcpy(_colors, line._colors, sizeof(Color) * _countColor);
	}*/

	return *this;
}

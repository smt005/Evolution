
#include "Line.h"

/*void Line::set(const float* const points, const unsigned int count, const unsigned short int type)
{
	if (points == nullptr || count < 2) {
		return;
	}

	_count = count;

	_points = new Point[_count];
	memcpy(_points, points, sizeof(Point) * _count);

	_type = type;
}*/

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

//	Greed

void Greed::set(const float width, const float height, const float step)
{
	if (width == 0.0f || step == 0.0f) {
		return;
	}

	
	{
		generateLines(_lineX, width, height, step, true);
		_lineX.color = Color::GREEN;

		float heavyPoints[] = { -10.0f, 0.0f, height, 10.0f, 0.0f, height };
		_heavyLineX.set(heavyPoints, 2);
		_heavyLineX.color = Color::GREEN;
		_heavyLineX.setLineWidth(3.0f);
	}

	{
		generateLines(_lineY, width, height, step, false);
		_lineY.color = Color::BLUE;

		float heavyPoints[] = { 0.0f, -10.0f, height, 0.0f, 10.0f, height };
		_heavyLineY.set(heavyPoints, 2);
		_heavyLineY.color = Color::BLUE;
		_heavyLineY.setLineWidth(3.0f);
	}

	{
		float points[] = { 0.0f, 0.0f, -10.0f, 0.0f, 0.0f, 10.0f };
		_lineZ.set( points, 2);
		_lineZ.color = Color::RED;

		float heavyPoints[] = { 0.0f, 0.0f, height - 10.0f, 0.0f, 0.0f, height + 10.0f };
		_heavyLineZ.set(points, 2);
		_heavyLineZ.color = Color::RED;
		_heavyLineZ.setLineWidth(3.0f);
	}
}

void Greed::generateLines(Line& line, const float width, const float height, const float step, const bool planeX)
{
	int countLine = width / step;
	++countLine;
	int countPoint = countLine * 2;

	Line::Point* points = new Line::Point[countPoint];

	float startPos = width * 0.5f;
	float pos = -(width * 0.5f);

	for (int i = 0; i < countPoint; i += 2)
	{
		points[i].data[0] = planeX ? -startPos : pos;
		points[i].data[1] = planeX ?  pos : -startPos;
		points[i].data[2] = height;

		points[i + 1].data[0] = planeX ? startPos : pos;
		points[i + 1].data[1] = planeX ? pos : startPos;
		points[i + 1].data[2] = height;

		pos += step;
	}

	line.set(points, countPoint, Line::LINE);
}

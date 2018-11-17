
#include "Color.h"

Color::Color()
{
	_dataColor[RED] = 1.0f;
	_dataColor[GREEN] = 1.0f;
	_dataColor[BLUE] = 1.0f;
	_dataColor[ALPHA] = 1.0f;
}

Color::Color(const float r, const float g, const float b) {
	_dataColor[RED] = r;
	_dataColor[GREEN] = g;
	_dataColor[BLUE] = b;
	_dataColor[ALPHA] = 1.0f;
}

Color::Color(const float r, const float g, const float b, const float a) {
	_dataColor[RED] = r;
	_dataColor[GREEN] = g;
	_dataColor[BLUE] = b;
	_dataColor[ALPHA] = a;
}

Color::Color(const int templateColor)
{
	switch (templateColor)
	{
	case RED: {
		_dataColor[RED] = 1.0f;
		_dataColor[GREEN] = 0.0f;
		_dataColor[BLUE] = 0.0f;
		_dataColor[ALPHA] = 1.0f;
	} break;
	case GREEN: {
		_dataColor[RED] = 0.0f;
		_dataColor[GREEN] = 1.0f;
		_dataColor[BLUE] = 0.0f;
		_dataColor[ALPHA] = 1.0f;
	} break;
	case BLUE: {
		_dataColor[RED] = 0.0f;
		_dataColor[GREEN] = 0.0f;
		_dataColor[BLUE] = 1.0f;
		_dataColor[ALPHA] = 1.0f;
	} break;
	case WHITE: {
		_dataColor[RED] = 1.0f;
		_dataColor[GREEN] = 1.0f;
		_dataColor[BLUE] = 1.0f;
		_dataColor[ALPHA] = 1.0f;
	} break;
	case BLACK: {
		_dataColor[RED] = 0.0f;
		_dataColor[GREEN] = 0.0f;
		_dataColor[BLUE] = 0.0f;
		_dataColor[ALPHA] = 1.0f;
	} break;
	default:
		break;
	}
}

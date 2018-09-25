
#pragma once

class Draw
{
public:
	static void setClearColor(const float r, const float g, const float b, const float a);
	static const float * const getClearColor();

	static void clearColor();
	static void prepare();

	static void drawBackround();
	static void drawTriangle();
};
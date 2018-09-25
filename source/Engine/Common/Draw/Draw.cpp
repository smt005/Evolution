
#include "windows.h"
#include <GL/gl.h> 
#include <GL/glu.h> 

#include "Draw.h"
#include "../../Window.h"

float _clearColor[4] = { 0.3f, 0.6f , 0.9f , 1.0f };

void Draw::setClearColor(const float r, const float g, const float b, const float a)
{
	_clearColor[0] = r;
	_clearColor[1] = g;
	_clearColor[2] = b;
	_clearColor[3] = a;

	glClearColor(r, g, b, a);
}

const float * const Draw::getClearColor()
{
	return _clearColor;
}

void Draw::clearColor()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Draw::prepare()
{
	int widthScreen = Window::width();
	int heightScreen = Window::height();
	glViewport(0.0, 0.0, widthScreen, heightScreen);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

float kRed = 0.001;
float red = 0.3f;
float kGreen = 0.002;
float green = 0.6f;
float kBlue = 0.001;
float blue = 0.9f;

void Draw::drawBackround()
{
	setClearColor(red, green, blue, 1.0f);

	{
		red += kRed;

		if (red > 1.0f) {
			kRed = -0.001;
		}

		if (red < 0.0f) {
			kRed = 0.001;
		}
	}

	{
		green += kGreen;

		if (green > 1.0f) {
			kGreen = -0.001;
		}

		if (green < 0.0f) {
			kGreen = 0.001;
		}
	}

	{
		blue += kBlue;

		if (blue > 1.0f) {
			kBlue = -0.001;
		}

		if (blue < 0.0f) {
			kBlue = 0.001;
		}
	}
}

void Draw::drawTriangle()
{

}

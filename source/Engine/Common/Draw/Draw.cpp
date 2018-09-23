
//#include <Windows.h>
//#include "../../../ThirdParty/glew/include/GL/glew.h"
//#include "../../../ThirdParty/glfw/include/GLFW/glfw3.h"
#include "Draw.h"

float _clearColor[4] = {0.3f, 0.6f , 0.9f , 1.0f };

void Draw::setClearColor(const float r, const float g, const float b, const float a)
{
	_clearColor[0] = r;
	_clearColor[1] = g;
	_clearColor[2] = b;
	_clearColor[3] = a;

	//glClearColor(r, g, b, a);
}

const float * const Draw::getClearColor()
{
	return _clearColor;
}

void Draw::clearColor()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

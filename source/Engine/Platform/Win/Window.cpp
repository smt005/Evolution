
#pragma once

#include <Windows.h>
//#include "../../../ThirdParty/glew/include/GL/glew.h"
#include "../../../ThirdParty/glfw/include/GLFW/glfw3.h"

#include "../../Window.h"
#include "../../Engine.h"

const int windowWidth = 600;
const int windowHeight = 300;
const char* windowTitle = "Window";

Window::Window()
{
	create();
}

Window::~Window()
{

}

bool Window::create()
{
	GLFWwindow* window;

	if (!glfwInit())
		return false;
	
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	//glfwSetMouseButtonCallback(window, ApplicationPlatform::mouseButtonCallback);
	//glfwSetCursorPosCallback(window, ApplicationPlatform::cursorPositionCallback);
	//glfwSetKeyCallback(window, ApplicationPlatform::keyCallback);

	glfwMakeContextCurrent(window);

	//if (glewInit() != GLEW_OK)
	//	return false;

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();

	return true;
}

void Window::update()
{
	for (int i = 0; i < 1000; ++i)
	{
		Core::Engine::update();
	}
}

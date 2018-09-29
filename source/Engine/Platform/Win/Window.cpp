
#pragma once

#include <Windows.h>
#include "glfw/include/GLFW/glfw3.h"
#include "jsoncpp/include/json/json.h"

#include "Window.h"
#include "Engine.h"
#include "Draw/Draw.h"

int windowWidth = 640;
int windowHeight = 480;
const char* windowTitle = "Window";

void cursorPositionCallback(GLFWwindow* Window, double x, double y);
void mouseButtonCallback(GLFWwindow* Window, int Button, int Action, int mods);
void keyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);

bool Window::create()
{
	GLFWwindow* window;

	if (!glfwInit())
		return false;
	
	const Json::Value& setting = Core::Engine::settingJson("window");
	if (!setting.empty()) {
		int windowWidthTemp = setting["width"].asInt();
		if (windowWidthTemp != 0) {
			windowWidth = windowWidthTemp;
		}

		int windowHeightTemp = setting["height"].asInt();
		if (windowHeightTemp != 0) {
			windowHeight = windowHeightTemp;
		}
	}

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwSetCursorPosCallback(window,	cursorPositionCallback);
	glfwSetMouseButtonCallback(window,	mouseButtonCallback);
	glfwSetKeyCallback(window,			keyCallback);

	glfwMakeContextCurrent(window);

	Core::Engine::init();

	while (!glfwWindowShouldClose(window))
	{
		Core::Engine::update();
		Core::Engine::draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();

	return true;
}

int Window::width() {
	return windowWidth;
}

int Window::height() {
	return windowHeight;
}

float Window::aspect()
{
	if (windowHeight == 0 || windowWidth == 0) {
		return 1.0f;
	}

	return (static_cast<float>(windowWidth) / static_cast<float>(windowHeight));
}

//---

void cursorPositionCallback(GLFWwindow* Window, double x, double y)
{

}

void mouseButtonCallback(GLFWwindow* Window, int Button, int Action, int mods)
{
	switch (Action)
	{
	case GLFW_PRESS:
	{
		switch (Button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			//Callback::tap_down();
		}
		break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
		{

		}
		break;
		case GLFW_MOUSE_BUTTON_RIGHT:
		{

		}
		break;
		}
	}
	break;

	case GLFW_RELEASE:
	{
		switch (Button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			//Callback::tap_up();
		}
		break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
		{

		}
		break;
		case GLFW_MOUSE_BUTTON_RIGHT:
		{

		}
		break;
		}
	}
	break;
	}
}

void keyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	switch (Action)
	{
	case GLFW_PRESS:
	{
		//Callback::buttonDown(Key);
	}
	break;

	case GLFW_RELEASE:
	{
		//Callback::buttonUp(Key);
	}
	break;
	}
}

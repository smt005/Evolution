
#pragma once

#include <Windows.h>
#include "glfw/include/GLFW/glfw3.h"
#include "jsoncpp/include/json/json.h"

#include "Window.h"
#include "Engine.h"
#include "Draw/Draw.h"

int windowWidth = 600;
int windowHeight = 300;
const char* windowTitle = "Window";

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

	//glfwSetMouseButtonCallback(window, ApplicationPlatform::mouseButtonCallback);
	//glfwSetCursorPosCallback(window, ApplicationPlatform::cursorPositionCallback);
	//glfwSetKeyCallback(window, ApplicationPlatform::keyCallback);

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
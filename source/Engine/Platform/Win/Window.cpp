
#pragma once

#include "../../Window.h"
#include "../../Engine.h"

Window::Window()
{
	update();
}

Window::~Window()
{

}

void Window::update()
{
	for (int i = 0; i < 1000; ++i)
	{
		Core::Engine::update();
	}
}

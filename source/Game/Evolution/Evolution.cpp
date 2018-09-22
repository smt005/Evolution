
#include "Evolution.h"
#include "../../Engine/Engine.h"

Evolution::Evolution()
{

}

Evolution::~Evolution()
{

}

void Evolution::update()
{
	updateGame();
}

void Evolution::updateGame()
{
	Core::Engine::log("test");
}

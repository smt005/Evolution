
#include "Evolution.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Common/Draw/Draw.h"

Evolution::Evolution()
{

}

Evolution::~Evolution()
{

}

void Evolution::init()
{
	Draw::setClearColor(0.3f, 0.6f, 0.9f, 1.0f);
	Draw::prepare();
}

void Evolution::update()
{
	updateGame();
}

void Evolution::updateGame()
{
	
}

void Evolution::draw()
{
	Draw::clearColor();
	Draw::drawBackround();
}

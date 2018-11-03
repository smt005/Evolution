#include "MicrobeGame_02.h"
#include "Microbe_02.h"
#include "Draw/Draw.h"

MicrobeGame_02::MicrobeGame_02()
{
}

MicrobeGame_02::~MicrobeGame_02()
{
}

void MicrobeGame_02::init()
{
	TemplateGame::init();
	Microbe_02::generate(150);

}

void MicrobeGame_02::update()
{
	std::function<void(void)> function = []() { PhysicCircle2D::updatePhysic(); };
	Microbe_02::updateItems(function);
	TemplateGame::update();
}

void MicrobeGame_02::draw()
{
	TemplateGame::draw();
	Draw::draw<Microbe_02>();
}

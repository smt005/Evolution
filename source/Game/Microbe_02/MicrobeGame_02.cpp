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
	Microbe_02::generate(50);

}

void MicrobeGame_02::update()
{
	Microbe_02::updateItems();
	TemplateGame::update();
}

void MicrobeGame_02::draw()
{
	TemplateGame::draw();
	Draw::draw<Microbe_02>();
}

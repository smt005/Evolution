#include "NeuronsGame.h"
#include "Draw/Draw.h"
#include "Draw/Camera.h"
#include "Callback/Callback.h"
#include "Neurons/Microbe.h"

NeuronsGame::NeuronsGame() {
}

NeuronsGame::~NeuronsGame() {
}

void NeuronsGame::init() {
	TemplateGame::init();

	Microbe::setFunction([]() { PhysicCircle2D::updatePhysic(); });

	int countMicrobe = 50;
	int countFood = 250;

#if _DEBUG
	countMicrobe = 5;
	countFood = 25;
#endif

	Microbe::generate(countMicrobe);
}

void NeuronsGame::update() {
	Microbe::updateItems();
	TemplateGame::update();
}

void NeuronsGame::draw() {
	TemplateGame::draw();
	Draw::draw<Microbe>();
}

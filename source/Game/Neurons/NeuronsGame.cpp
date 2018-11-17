#include "NeuronsGame.h"
#include "Draw/Draw.h"
#include "Draw/Camera.h"
#include "Callback/Callback.h"
#include "Neurons/MicrobeNeurons.h"

NeuronsGame::NeuronsGame() {
}

NeuronsGame::~NeuronsGame() {
}

void NeuronsGame::init() {
	TemplateGame::init();

	MicrobeNeurons::setFunction([]() { PhysicCircle2D::updatePhysic(); });

	int countMicrobe = 50;
	int countFood = 250;

#if _DEBUG
	countMicrobe = 5;
	countFood = 25;
#endif

	MicrobeNeurons::generate(countMicrobe);
}

void NeuronsGame::update() {
	MicrobeNeurons::updateItems();
	TemplateGame::update();
}

void NeuronsGame::draw() {
	Draw::draw<MicrobeNeurons>();
	TemplateGame::draw();
}

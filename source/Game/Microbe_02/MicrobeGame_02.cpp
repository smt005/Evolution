#include "MicrobeGame_02.h"
#include "Microbe_02.h"
#include "Draw/Draw.h"
#include "Draw/Camera.h"
#include "Callback/Callback.h"
#include "Microbe_02/Cells/CellBrain.h"

MicrobeGame_02::MicrobeGame_02() {
}

MicrobeGame_02::~MicrobeGame_02() {
}

void MicrobeGame_02::init() {
	TemplateGame::init();

	_callback->add(Engine::CallbackType::MOVE, [this](const Engine::CallbackEventPtr& callbackEventPtr) {
		CellBrain::targetPos = Camera::current.corsorCoord();
	});

	Microbe_02::setFunction([]() { PhysicCircle2D::updatePhysic(); });
	Microbe_02::generate(150);

}

void MicrobeGame_02::update() {
	Microbe_02::updateItems();
	TemplateGame::update();
}

void MicrobeGame_02::draw() {
	TemplateGame::draw();
	Draw::draw<Microbe_02>();
}

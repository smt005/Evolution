
#include "Microbe.h"
#include "MicrobeBrain.h"
#include "MicrobeMouth.h"
#include "MicrobeMover.h"
#include "MicrobeEnergy.h"
#include "DNA.h"
#include "Core.h"

using namespace microbe;

Microbe::Microbe() {
	Engine::Core::log("Microbe::Microbe id: " + getIdAsString(3));
}

Microbe::Microbe(const DnaPtr& DNA) {
	_DNA = DNA;
	std::string isStr = _DNA ? _DNA->name() : "EMPTY";
	Engine::Core::log("Microbe::Microbe id: " + getIdAsString(3) + ' ' + isStr);
}

Microbe::Microbe(const std::string& idDNA) {
	_DNA = DNA::getByName(idDNA);
	std::string isStr = _DNA ? _DNA->name() : "EMPTY";
	Engine::Core::log("Microbe::Microbe id: " + getIdAsString(3) + ' ' + isStr);
}

void Microbe::update()
{
	Engine::Core::log("Microbe::update id: " + getIdAsString(3));

	for (auto& cellPtr : _childs) {
		if (cellPtr) {
			cellPtr->update();
		}
	}
}

void Microbe::generate()
{
	if (!_DNA) {
		return;
	}

	for (auto& dnaCell : _DNA->getCells())
	{
		switch (dnaCell.type)
		{
			case  Cell::BRAIN :
			{
				Cell* cell = new Brain();
				_childs.emplace_back(cell); 
			} break;

			case  Cell::ENERGY:
			{
				Cell* cell = new Energy();
				_childs.emplace_back(cell);
			} break;

			case  Cell::MOUTH:
			{
				Cell* cell = new Mouth();
				_childs.emplace_back(cell);
			} break;

			case  Cell::MOVER:
			{
				Cell* cell = new Mover();
				_childs.emplace_back(cell);
			};
		}
	}
}

//	static

std::vector<MicrobePtr> Microbe::_microbes;

void Microbe::updateMicrobes() {
	for (auto& micribePtr : _microbes) {
		if (micribePtr) {
			micribePtr->update();
		}
	}
}

void Microbe::clear() {
	_microbes.clear();
}

void Microbe::generateMicrobes()
{
	clear();

	for (int i = 0; i < 10; ++i)
	{
		Microbe* microbe = new Microbe("376");
		microbe->generate();
		_microbes.emplace_back(microbe);
	}

	Engine::Core::log("log");
}

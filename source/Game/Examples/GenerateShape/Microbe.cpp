
#include "Microbe.h"
#include "MicrobeBrain.h"
#include "MicrobeMouth.h"
#include "MicrobeMover.h"
#include "MicrobeEnergy.h"
#include "DNA.h"
#include "Core.h"

using namespace microbe;

//	Microbe

Microbe::Microbe() {
	Engine::Core::log("Microbe::Microbe id: " + getIdAsString(3));
}

Microbe::Microbe(const DnaPtr& dnaPtr) {
	_dnaPtr = dnaPtr;
	std::string isStr = _dnaPtr ? _dnaPtr->name() : "EMPTY";
	Engine::Core::log("Microbe::Microbe id: " + getIdAsString(3) + ' ' + isStr);
}

Microbe::Microbe(const std::string& idDNA) {
	_dnaPtr = DNA::getByName(idDNA);
	std::string isStr = _dnaPtr ? _dnaPtr->name() : "EMPTY";
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

void Microbe::generate(const MicrobeWptr& microbeWptr)
{
	if (!_dnaPtr || microbeWptr.expired()) {
		return;
	}
	
	for (auto& dnaCell : _dnaPtr->getCells())
	{
		switch (dnaCell.type)
		{
			case  Cell::BRAIN :
			{
				Cell* cell = new Brain(microbeWptr, dnaCell);
				_childs.emplace_back(cell); 
			} break;

			case  Cell::ENERGY:
			{
				Cell* cell = new Energy(microbeWptr, dnaCell);
				_childs.emplace_back(cell);
			} break;

			case  Cell::MOUTH:
			{
				Cell* cell = new Mouth(microbeWptr, dnaCell);
				_childs.emplace_back(cell);
			} break;

			case  Cell::MOVER:
			{
				Cell* cell = new Mover(microbeWptr, dnaCell);
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
		MicrobePtr microbePtr = MicrobePtr(microbe);
		MicrobeWptr microbeWptr = microbePtr;
		microbe->generate(microbeWptr);

		_microbes.push_back(microbePtr);
	}

	Engine::Core::log("log");
}

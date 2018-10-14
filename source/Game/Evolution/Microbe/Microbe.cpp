
#include "Microbe.h"
#include "MicrobeBrain.h"
#include "MicrobeMouth.h"
#include "MicrobeMover.h"
#include "MicrobeEnergy.h"
#include "DNA.h"
#include  "Common/Help.h"
#include "Core.h"

using namespace microbe;

//	Microbe

Microbe::Microbe()
	: _health(100.0f)
{
}

Microbe::Microbe(const DnaPtr& dnaPtr)
	: _health(100.0f)
{
	_dnaPtr = dnaPtr;
}

Microbe::Microbe(const std::string& idDNA)
	: _health(100.0f)
{
	_dnaPtr = DNA::getByName(idDNA);
}

void Microbe::update()
{
	_currentEvents = _nextEvents;
	_nextEvents = nullptr;

	if (_currentEvents)
	{

		for (auto& event : (*_currentEvents))
		{
			switch (event->getType())
			{
			case Event::MOVE: {
				EventMove* eventMove = (EventMove*)event->getPoint();
				short int moverId = eventMove->getMoverId();
				bool _state = eventMove->getState();
				Event::Callback callback = eventMove->getCallback();

				if (moverId >= 0 && moverId < _moverChilds.size()) {
					auto mouthPtr = _moverChilds[0];
					if (mouthPtr) {
						mouthPtr->setState(_state);
					}
				}
			} break;

			case Event::ENERGY_GET: {
				if (!_energyChilds.size()) {
					break;
				}

				EventEnergyGet* eventEnergyGet = (EventEnergyGet*)event->getPoint();
				float valueWant = eventEnergyGet->getValueWant();
				Event::Callback callback = eventEnergyGet->getCallback();

				EnergyPtr energy = _energyChilds.front();
				callback(energy->apply(valueWant));
			} break;

			case Event::EAT: {
				if (!_energyChilds.size()) {
					break;
				}

				EventEat* eventEnergyGet = (EventEat*)event->getPoint();
				float valueDamage = eventEnergyGet->getValueDamage();
				MicrobePtr target = eventEnergyGet->getTarget();
				Event::Callback callback = eventEnergyGet->getCallback();

				float value = 0.0f;
				target->applyDamage(value, valueDamage);

				if (value > 0.0f) {
					for (auto& cellPtr : _energyChilds) {
						if (cellPtr) {
							cellPtr->load(value);
						}
					}
				}
			} break;
			default:
				break;
			}
		}

		delete _currentEvents;
		_currentEvents = nullptr;

	}

	for (auto& cellPtr : _brainChilds) {
		if (cellPtr) {
			cellPtr->update();
		}
	}

	for (auto& cellPtr : _energyChilds) {
		if (cellPtr) {
			cellPtr->update();
		}
	}

	for (auto& cellPtr : _mouthChilds) {
		if (cellPtr) {
			cellPtr->update();
		}
	}

	for (auto& cellPtr : _moverChilds) {
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
				Brain* cell = new Brain(microbeWptr, dnaCell);
				_brainChilds.emplace_back(cell);
			} break;

			case  Cell::ENERGY:
			{
				Energy* cell = new Energy(microbeWptr, dnaCell);
				_energyChilds.emplace_back(cell);
			} break;

			case  Cell::MOUTH:
			{
				Mouth* cell = new Mouth(microbeWptr, dnaCell);
				_mouthChilds.emplace_back(cell);
			} break;

			case  Cell::MOVER:
			{
				Mover* cell = new Mover(microbeWptr, dnaCell);
				_moverChilds.emplace_back(cell);
			};
		}
	}

	make();
	setTexture("Textures/Cell.png");
}

void Microbe::make()
{
	_count = (_brainChilds.size() + _energyChilds.size() + _mouthChilds.size() + _moverChilds.size() + 1) * 3;
	_points = new Point[_count];
	_texCoord = new TexCoord[_count];

	size_t index = 3;

	for (auto& cell : _brainChilds) {
		if (cell) {
			makeData(index, *cell);
		}
	}

	for (auto& cell : _energyChilds) {
		if (cell) {
			makeData(index, *cell);
		}
	}

	for (auto& cell : _mouthChilds) {
		if (cell) {
			makeData(index, *cell);
		}
	}

	for (auto& cell : _moverChilds) {
		if (cell) {
			makeData(index, *cell);
		}
	}

	Cell cellTemp;
	index = 0;
	makeData(index, cellTemp);
}

void Microbe::makeData(size_t& index, const Cell& cell)
{
	Point*	  points = &_points[index];
	TexCoord* texCoord = &_texCoord[index];

	float scale = cell._size;
	const float* const pos = cell._pos;

	for (size_t i = 0; i < 3; ++i) {
		points[i].data[0] = pointsStatic[i].data[0] * scale;
		points[i].data[1] = pointsStatic[i].data[1] * scale;
		points[i].data[2] = pointsStatic[i].data[2] * scale;

		points[i].data[0] += pos[0];
		points[i].data[1] += pos[1];
		points[i].data[2] += (pos[2] + (static_cast<float>(index) * 0.01f));
	}

	memcpy(texCoord, texCoordStatic, sizeof(TexCoord) * 3);

	index += 3;
}

//	static

Triangle::Point Microbe::pointsStatic[3] = {	-0.425f, -0.9f, 0.0f,
												0.575f, 0.0f, 0.0f,
												-0.425f, 0.9f, 0.0f };

Triangle::TexCoord Microbe::texCoordStatic[3] = {	1.715f, 0.0f,
													0.0f, 0.0f,
													0.0f, 1.715f };
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

	bool switchVar = false;

	for (int i = 0; i < 1; ++i)
	{
		switchVar = !switchVar;
		Microbe* microbe = new Microbe(switchVar ? "0000" : "0001");
		MicrobePtr microbePtr = MicrobePtr(microbe);
		MicrobeWptr microbeWptr = microbePtr;
		microbe->generate(microbeWptr);

		microbe->setPos( {	help::random_f(-10.0f, 10.0f),
							help::random_f(-10.0f, 10.0f),
							1.5f} );

		_microbes.push_back(microbePtr);
	}
}

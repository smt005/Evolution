#include "Microbe.h"
#include "MicrobeMouth.h"
#include "Core.h"
#include "Common/Help.h"

using namespace microbe;

Mouth::Mouth(const MicrobeWptr& core, const DNA::ValueCell& valueCell)
	: _valueNeed(0.1f)
	, _valueDamage(1.0f)
{
	init(core, valueCell);
}

void Mouth::update()
{
	const std::vector<MicrobePtr>& microbes = Microbe::getMicrobes();

	if (_core.expired()) {
		return;
	}

	auto core = _core.lock();

	Event::Callback callback = [this, core](bool state) {
		if (state) {
			eat();
		}
	};

	for (auto& microbe : microbes)
	{
		if (microbe->getId() == core->getId()) continue;

		float dist = help::distXY(microbe->getPos(), core->getPos());
		if (dist < 1.0f) {
			_target = microbe;

			Event* event = new EventEnergyGet(_valueNeed, callback);
			EventPtr eventPtr = EventPtr(event);
			core->addEvent(eventPtr);
		}
	}
}

void Mouth::eat()
{
	if (_core.expired()) {
		return;
	}

	auto core = _core.lock();

	Event::Callback callback = [this, core](bool state) {
		if (state) {
			
		}
	};

	Event* event = new EventEat(_target, _valueDamage, callback);
	EventPtr eventPtr = EventPtr(event);
	core->addEvent(eventPtr);
}
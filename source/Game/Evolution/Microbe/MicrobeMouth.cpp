#include "Microbe.h"
#include "MicrobeMouth.h"
#include "Core.h"
#include "Common/Help.h"

using namespace microbe;

void Mouth::update()
{
	const std::vector<MicrobePtr>& microbes = Microbe::getMicrobes();

	if (_core.expired()) {
		return;
	}

	auto core = _core.lock();

	Event::Callback callback = [this, core](bool state) {
		if (state) {

		}
	};

	for (auto& microbe : microbes)
	{
		if (microbe->getId() == core->getId()) continue;

		float dist = help::distXY(microbe->getPos(), core->getPos());
		if (dist) {
			Event* event = new EventEat(microbe, callback);
			EventPtr eventPtr = EventPtr(event);
			core->addEvent(eventPtr);
		}
	}
}

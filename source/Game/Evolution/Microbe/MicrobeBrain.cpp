
#include "MicrobeBrain.h"
#include "Core.h"
#include "Event.h"
#include <corecrt_math_defines.h>

using namespace microbe;

void Brain::update()
{
	if (_core.expired()) {
		return;
	}

	auto core = _core.lock();

	bool state = lastState;
	++testTact;

	if (testTact == 1000) {
		testTact = -1000;
		state = false;
	}

	if (testTact == 0) {
		state = true;
	}

	if (lastState != state) {
		lastState = state;

		Event* event = new EventMove(0, state, 0);
		EventPtr eventPtr = EventPtr(event);
		core->addEvent(eventPtr);
	}
}

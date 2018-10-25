#include "Microbe.h"
#include "MicrobeMover.h"
#include "Core.h"
#include "Event.h"
#include "jsoncpp/include/json/json.h"

using namespace microbe;

Mover::Mover(const MicrobeWptr& core, const DNA::ValueCell& valueCell)
	: _state(false)
	, _valueWant(0.25f)
{
	init(core, valueCell);

	if (valueCell.data.empty()) {
		return;
	}

	const Json::Value& jsonValue = valueCell.data;

	if (jsonValue["v"].isArray() && !jsonValue["v"].empty()) {
		_vec.x = jsonValue["v"][0].asFloat();
		_vec.y = jsonValue["v"][1].asFloat();
		_vec.z = jsonValue["v"][2].asFloat();
	}
}

void Mover::update()
{
	if (!_state || _core.expired()) {
		return;
	}

	auto core = _core.lock();

	Event::Callback callback = [this, core](bool state) {
		if (state) {
			glm::vec3 pos = core->getPos();

			core->_moveVector = _vec * Engine::Core::deltaTime();
			core->_nextPos = pos + core->_moveVector;
		}
	};

	Event* event = new EventEnergyGet(_valueWant, callback);
	EventPtr eventPtr = EventPtr(event);
	core->addEvent(eventPtr);
}

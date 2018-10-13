#include "Microbe.h"
#include "MicrobeMover.h"
#include "Core.h"
#include "jsoncpp/include/json/json.h"

using namespace microbe;

Mover::Mover(const MicrobeWptr& core, const DNA::ValueCell& valueCell)
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
	if (_core.expired()) {
		return;
	}

	auto core = _core.lock();

	glm::vec3 pos = core->getPos();

	pos += _vec;

	core->setPos(pos);
}

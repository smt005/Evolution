#include "Microbe.h"
#include "MicrobeEnergy.h"
#include "Core.h"

using namespace microbe;

Energy::Energy(const MicrobeWptr& core, const DNA::ValueCell& valueCell)
{
	init(core, valueCell);

	if (valueCell.data.empty()) {
		return;
	}

	const Json::Value& jsonValue = valueCell.data;

	_maxValue = jsonValue["max"].asFloat();
	_value = _maxValue;
}

void Energy::update()
{

}

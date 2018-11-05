#include "Cell.h"
#include "Microbe_02/MicrobeEvent_02.h"
#include <functional>

bool Cell::requestEnergy()
{
	float needEnergy = _maxStockEnergy - _stockEnergy;

	if (needEnergy > 0.0f) {
		std::function<void(float)> function = [this](const float canAddEnergy) {
			_stockEnergy += canAddEnergy;
		};

		DataEnergyEvent* data = new DataEnergyEvent();
		data->function = function;
		data->needEnergy = needEnergy;
		Microbe_02::Event eventEnergy(data);

		_core->addEvent(eventEnergy);
	}

	return (_stockEnergy - _consumption) <= 0.0f ? false : true;
}

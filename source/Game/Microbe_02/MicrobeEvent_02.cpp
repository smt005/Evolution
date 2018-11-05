
#include "Microbe_02.h"
#include "MicrobeEvent_02.h"
#include "Cells/Cell.h"
#include "Cells/CellEnergy.h"
#include "Cells/CellMove.h"
#include "Cells/CellMouth.h"
#include "Cells/CellBrain.h"

void Microbe_02::applyEvents()
{
	for (auto& eventItem : _events) {
		if (!eventItem.getData<Event::Data>()) continue;

		switch (eventItem.getType())
		{
		case Microbe_02::Event::MOVE : {
			applyEvent(*eventItem.getData<DataMoveEvent>());
		} break;
		case Microbe_02::Event::ENERGY: {
			applyEvent(*eventItem.getData<DataEnergyEvent>());
		} break;
		default:
			break;
		}
	}

	_events.clear();
}

void Microbe_02::applyEvent(DataMoveEvent& data) {
	if (cellMove) {
		cellMove->vectorMove = data.move;
	}
}

void Microbe_02::applyEvent(DataEnergyEvent& data) {
	if (cellEnergy && data.function) {
		float canEnergy = data.needEnergy;
		float leftEnergy = cellEnergy->_stockEnergy - canEnergy;

		if (leftEnergy > 0.0f) {
			cellEnergy->_stockEnergy = leftEnergy;
		}
		else {
			cellEnergy->_stockEnergy = 0.0f;
			canEnergy += leftEnergy;
		}

		data.function(canEnergy);
	}
}

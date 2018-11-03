
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
			moveEvent(*eventItem.getData<DataMoveEvent>());
		} break;
		default:
			break;
		}
	}
}

void Microbe_02::moveEvent(DataMoveEvent& dataMove) {
	if (cellMove) {
		cellMove->vectorMove = dataMove.move;
	}
}

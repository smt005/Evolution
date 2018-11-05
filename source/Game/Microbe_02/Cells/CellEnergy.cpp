
#include "CellEnergy.h"

void CellEnergy::action()
{
	if (!requestEnergy()) {
		return;
	}
}

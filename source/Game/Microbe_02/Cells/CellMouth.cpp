
#include "CellMouth.h"

void CellMouth::action()
{
	if (!requestEnergy()) {
		return;
	}
}

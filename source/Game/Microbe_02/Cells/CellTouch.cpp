
#include "CellTouch.h"
#include "CellBrain.h"
#include "CellEnergy.h"
#include "Microbe_02/Microbe_02.h"
#include "Microbe_02/MicrobeEvent_02.h"
#include "Microbe_02/Food_02.h"
#include <glm/mat4x4.hpp>

void CellTouch::init() {

}

void CellTouch::action()
{
	if (!requestEnergy()) {
		return;
	}

	if (!_core) {
		return;
	}


}

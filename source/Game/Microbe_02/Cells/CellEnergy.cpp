
#include "CellEnergy.h"
#include "Microbe_02/Microbe_02.h"

void CellEnergy::action()
{
	/*if (!requestEnergy()) {
		return;
	}*/

	if (!_core) {
		return;
	}

	if (_core->_live) {
		float k = _stockEnergy / _maxStockEnergy;
		*_core->_live = k;
	}

	float live = _core->_live ? *_core->_live : 0.0f;

	if (live > 0.0f) {
		_core->_triangle->setRed(1.0f - live);
		_core->_triangle->setGreen(live);
		_core->_triangle->setBlue(live);
	}
	else {
		_core->_triangle->setColor(Color::BLACK);
	}
}

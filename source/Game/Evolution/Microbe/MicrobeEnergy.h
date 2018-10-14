#pragma once

#include "Microbe.h"

namespace microbe
{

class Energy final : public Cell
{
public:
	Energy() {}
	Energy(const MicrobeWptr& core, const DNA::ValueCell& valueCell);
	unsigned short int type() override { return Cell::ENERGY; }

	void update() override;
	inline bool apply(const float valueVant) {
		if (_value > valueVant) {
			_value -= valueVant;
			return true;
		}
		else {
			return false;
		}
	}

	inline void load(float& value) {
		float newValue = _value + value;
		if (newValue <= _maxValue) {
			value = 0.0f;
		}
		else {
			value = newValue - _maxValue;
		}
	}
private:
	float _value;
	float _maxValue;
};

};	// microbe
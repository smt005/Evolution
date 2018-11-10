#pragma once

#include "Neuron.h"
#include "Microbe_02/Microbe_02.h"
#include "Microbe_02/Cells/CellBrain.h"
#include "Microbe_02/Cells/CellEnergy.h"
#include "Microbe_02/Cells/CellMouth.h"
#include "Microbe_02/Cells/CellMove.h"
#include "Microbe_02/Cells/CellTouch.h"

class NeuronTest final : public Neuron
{
public:
	Type getType() override {
		return TEST;
	}
	void function() override {
		_value = true;
	}
	
public:
	//Microbe_02*	core	= nullptr;

	//Neuron*	brainIn		= nullptr;
	//Neuron*	energyIn	= nullptr;
	//Neuron*	mouthIn		= nullptr;
	//Neuron*	moveIn		= nullptr;
	//Neuron*	touchIn		= nullptr;

	/*Neuron*	brainOut	= nullptr;
	Neuron*	energyOut	= nullptr;
	Neuron*	mouthOut	= nullptr;
	Neuron*	moveOut		= nullptr;
	Neuron*	touchOut	= nullptr;*/
};

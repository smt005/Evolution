#pragma once

#include "Neuron.h"

class NeuronTest final : public Neuron
{
public:
	NeuronTest() { _debugName = "NeuronTest"; }
	void action() override;

private:

};

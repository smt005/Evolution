#include "CellBrain.h"
#include "CellMove.h"
#include "Microbe.h"
#include "NeuronTest.h"

CellBrain::~CellBrain()
{
}

void CellBrain::action()
{
	for (NeuronPtr& neuron : _neurons) {
		neuron->action();
	}
}

void CellBrain::init(Microbe* core)
{
	_core = core;
	if (!_core) {
		return;
	}

	{
		auto cellMove = _core->_cellsMove[0];
		NeuronPtr outNeuron = cellMove->outNeuron;
		NeuronPtr inNeuron = cellMove->inNeuron;
		NeuronPtr inBrain = NeuronPtr(new NeuronTest);

		{
			Neuron* neuron = outNeuron->getPtr();
			inBrain->_source.push_back(neuron);
		}

		{
			Neuron* neuron = inBrain->getPtr();
			inNeuron->_source.push_back(neuron);
		}

		_neurons.push_back(outNeuron);
		_neurons.push_back(inBrain);
		_neurons.push_back(inNeuron);
	}
}

#include "CellMove.h"
#include "Microbe.h"

void CellMove::action()
{
	glm::vec3 vector(_vector);
	vector.z = 0.0f;
	_core->_physic->setVectorPhysic(vector);
}

void CellMove::init(Microbe* core)
{
	_core = core;
	
	{
		Neuron* neuron = new NeuronMoveIn(this);
		inNeuron = NeuronPtr(neuron);
	}

	{
		Neuron* neuron = new NeuronMoveOut(this);
		outNeuron = NeuronPtr(neuron);
	}
}

//---

void CellMove::NeuronMoveIn::action()
{
	if (_source.empty()) {
		return;
	}

	Neuron* neuron = _source[0];
	_cellMove->_value = neuron->_value;
}

void CellMove::NeuronMoveOut::action()
{
	_value = _cellMove->_value;
}

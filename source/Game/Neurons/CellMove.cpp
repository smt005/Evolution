#include "CellMove.h"
#include "Microbe.h"

void CellMove::action()
{
	if (_state) {
		glm::vec3 vector(0.0f);
		vector.x = 0.01f;
		_core->_physic->setVectorPhysic(vector);
	}
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
	_cellMove->_state = neuron->_value > 0.0f ? true : false;
}

void CellMove::NeuronMoveOut::action()
{
	_value = _cellMove->_state == true ? 1.0f : 0.0f;
}

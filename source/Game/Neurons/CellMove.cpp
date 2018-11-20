#include "CellMove.h"
#include "Microbe.h"

glm::vec3 CellMove::_rotateVector = glm::vec3(0.0f, 0.0f, 1.0f);

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

//---

void CellMove::action()
{
	_vectorPhysic = _vector * _value;
	_anglePhysic += _angle * _value;

	glm::vec3 vector(1.0f, 0.0f, 0.0f);
	vector.z = 0.0f;
	rotateVector(vector, _anglePhysic);
	vector *= _vectorPhysic;

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

void CellMove::rotateVector(glm::vec3& vector, const float angle)
{
	if (angle == 0.0f) {
		return;
	}

	vector.x = sin(angle);
	vector.y = cos(angle);
	normalize(vector);
}
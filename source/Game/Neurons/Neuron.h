#pragma once

#include <memory>
#include <vector>

class Neuron;
typedef std::shared_ptr<Neuron> NeuronPtr;

class Neuron
{
public:
	Neuron() : _value (0.0f) {}
	virtual ~Neuron() {}
	virtual void action() {}

	Neuron* getPtr() { return this; }
	void setValue(const float value) { _value = value; }
	float getValue() { return _value; }

public:
	float _value;
	std::vector<Neuron*> _source;

public:
	std::string _debugName = "Neuron";
};

class NeuronInterface
{
public:
	NeuronInterface() {
		inNeuron = NeuronPtr(new Neuron());
		outNeuron = NeuronPtr(new Neuron());
	}
	virtual ~NeuronInterface() {}

public:
	NeuronPtr inNeuron;
	NeuronPtr outNeuron;
};

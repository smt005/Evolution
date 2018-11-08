#pragma once

#include <memory>
#include <vector>

class Neuron;
typedef std::shared_ptr<Neuron> NeuronPtr;
class Cell;
typedef std::shared_ptr<Cell> CellPtr;

class Neuron
{
public:
	Neuron() {}
	Neuron(const std::vector<NeuronPtr>& inNeurons, const std::vector<NeuronPtr>& outNeurons) {
		_inNeurons = inNeurons;
		_outNeurons = outNeurons;
	}
	virtual ~Neuron() {}

private:
	std::vector<NeuronPtr> _inNeurons;
	std::vector<NeuronPtr> _outNeurons;
};

//---

class NeuronInterface : public Neuron
{
public:
	NeuronInterface() { }
	NeuronInterface(const std::vector<CellPtr>& cells, const std::vector<NeuronPtr>& neurons) {

	}
	~NeuronInterface() {}

private:

};

//---

class NeuronIn final : public Neuron
{
public:
	NeuronIn() {}
	~NeuronIn() {}

private:

};

//---

class NeuronOut final : public Neuron
{
public:
	NeuronOut() {}
	~NeuronOut() {}

private:

};

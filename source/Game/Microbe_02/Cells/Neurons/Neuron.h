#pragma once

#include <memory>
#include <vector>

class Neuron;
class Cell;
typedef std::shared_ptr<Cell> CellPtr;

class Neuron
{
public:
	typedef unsigned int Type;
	enum {
		NONE,
		AND,
		OR,
		AND_NO,
		OR_NO,
		TEST
	};

public:
	Neuron() {}
	void add(const std::vector<Neuron*>& neurons) {
		_sourceNeurons = neurons;
	}
	void add(Neuron* const neuron) {
		_sourceNeurons.push_back(neuron);
	}
	virtual ~Neuron() {}
	virtual void function() {};
	virtual Type getType() {
		return NONE;
	}

public:
	float _value;
	std::vector<Neuron*> _sourceNeurons;
};

//---

class NeuronAnd final : public Neuron
{
public:
	void function() override {
		size_t size = _sourceNeurons.size();

		if (size > 1) {
			_value = _sourceNeurons[0]->_value;
			for (size_t i = 1; i < size; ++i) {
				_value *= _sourceNeurons[i]->_value;
			}	 
		}
		else if (size == 1) {
			_value = _sourceNeurons[0]->_value;
		}
	}
	virtual Type getType() {
		return AND;
	}
};

//---

class NeuronOr final : public Neuron
{
public:
	void function() override {
		size_t size = _sourceNeurons.size();

		if (size > 1) {
			_value = _sourceNeurons[0]->_value;
			for (size_t i = 1; i < size; ++i) {
				_value += _sourceNeurons[i]->_value;
			}

			_value /= static_cast<float>(size);
		}
		else if (size == 1) {
			_value = _sourceNeurons[0]->_value;
		}
	}
	virtual Type getType() {
		return OR;
	}
};

//---

class NeuronAndNo final : public Neuron
{
public:
	void function() override {
		size_t size = _sourceNeurons.size();

		if (size > 1) {
			_value = _sourceNeurons[0]->_value;
			for (size_t i = 1; i < size; ++i) {
				_value *= _sourceNeurons[i]->_value;
			}
		}
		else if (size == 1) {
			_value = _sourceNeurons[0]->_value;
		}

		_value = 1.0f - _value;
	}
	virtual Type getType() {
		return AND_NO;
	}
};

//---

class NeuronOrNo final : public Neuron
{
public:
	void function() override {
		size_t size = _sourceNeurons.size();

		if (size > 1) {
			_value = _sourceNeurons[0]->_value;
			for (size_t i = 1; i < size; ++i) {
				_value += _sourceNeurons[i]->_value;
			}

			_value /= static_cast<float>(size);
		}
		else if (size == 1) {
			_value = _sourceNeurons[0]->_value;
		}

		_value = 1.0f - _value;
	}
	virtual Type getType() {
		return OR_NO;
	}
};

//---

class NeuronInterface
{
public:
	~NeuronInterface() {}

public:
	Neuron* inNeuron;
	Neuron outNeuron;
	bool state = false;
};

//---

class Brain
{
public:
	Brain() {}
	virtual ~Brain() {
		for (Neuron* neuron : _neurons) {
			if (neuron) {
				delete neuron;
			}
		}
	}

	void add(Neuron* neuron) {
		_neurons.push_back(neuron);
	}
	void update() {
		for (Neuron* neuron : _neurons) {
			neuron->function();
		}
	}

private:
	std::vector<Neuron*> _neurons;
};

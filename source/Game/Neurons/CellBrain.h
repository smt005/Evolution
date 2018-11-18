#pragma once

#include "Cell.h"
#include "Neuron.h"
#include <vector>

class CellBrain;
typedef std::shared_ptr<CellBrain> CellBrainPtr;

class CellBrain final :public Cell
{
public:
	~CellBrain();
	void action() override;
	void init(Microbe* core) override;

private:
	std::vector<NeuronPtr> _neurons;
};

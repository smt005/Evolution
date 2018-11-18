#pragma once

#include "Cell.h"
#include "Neuron.h"

class CellBrain;
class NeuronMoveIn;
class NeuronMoveOut;
class CellMove;
typedef std::shared_ptr<CellMove> CellMovePtr;

class CellMove final : public Cell, public NeuronInterface
{
	friend CellBrain;
	friend NeuronMoveIn;
	friend NeuronMoveOut;
public:
	class NeuronMoveIn final : public Neuron
	{
	public:
		NeuronMoveIn(CellMove* cellMove) { _cellMove = cellMove; _debugName = "CellMove::NeuronMoveIn"; }
		void action() override;
	private:
		CellMove* _cellMove;
	};

	class NeuronMoveOut final : public Neuron
	{
	public:
		NeuronMoveOut(CellMove* cellMove) { _cellMove = cellMove; _debugName = "CellMove::NeuronMoveOut"; }
		void action() override;
	private:
		CellMove* _cellMove;
	};
	
public:
	CellMove() : _state(false) {}
	void action() override;
	void init(Microbe* core) override;

private:
	bool _state;
};

#pragma once

#include "Cell.h"
#include "Neuron.h"
#include <glm/vec3.hpp>

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
	
	//---

public:
	CellMove()
		: _value(0.0f)
		, _vector(0.01f)
		, _angle(0.001f)
		, _vectorPhysic(0.0f)
		, _anglePhysic(0.0f) {}
	void action() override;
	void init(Microbe* core) override;

private:
	void rotateVector(glm::vec3& vector, const float angle);

private:
	bool _value;

	float _vector;
	float _angle;

	float _vectorPhysic;
	float _anglePhysic;

private:
	static glm::vec3 _rotateVector;
};

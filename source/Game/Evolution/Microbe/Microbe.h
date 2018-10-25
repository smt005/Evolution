#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Object/Identify.h"
#include "Object/Position.h"
#include "Object/Triangle.h"
#include "DNA.h"
#include "Event.h"

namespace microbe
{

class Cell;
class Brain;
class Energy;
class Mouth;
class Mover;
class Microbe;

typedef std::shared_ptr<Cell> CellPtr;
typedef std::shared_ptr<Brain> BrainPtr;
typedef std::shared_ptr<Energy> EnergyPtr;
typedef std::shared_ptr<Mouth> MouthPtr;
typedef std::shared_ptr<Mover> MoverPtr;
typedef std::shared_ptr<Microbe> MicrobePtr;
typedef std::weak_ptr<Microbe> MicrobeWptr;

class Cell
{
public:
	enum
	{
		NONE,
		BRAIN,
		ENERGY,
		MOUTH,
		MOVER
	};

	typedef unsigned short int Type;

public:
	Cell()
		: _size(1.0f)
	{
		_pos[0] = 0.0f;
		_pos[1] = 0.0f;
		_pos[2] = 0.0f;
	}
	void init(const MicrobeWptr& core, const DNA::ValueCell& valueCell)
	{
		if (core.expired()) {
			return;
		}

		_core = core;

		_pos[0] = cosf(valueCell.angle) * valueCell.dist;
		_pos[1] = sinf(valueCell.angle) * valueCell.dist;
		_pos[2] = 0.0f;

		_size = valueCell.size;

	}
	virtual ~Cell() {}
	virtual unsigned short int type() { return Cell::NONE; }
	virtual void update() {}
	


public:
	MicrobeWptr _core;
	float _size;
	float _pos[3];
};

class Microbe final : public Triangle, public UniqueId
{
public:
	friend Mover;

	Microbe();
	Microbe(const DnaPtr& DNA);
	Microbe(const std::string& idDNA);
	void update();
	void updateMove();
	void generate(const MicrobeWptr& microbeWptr);

	void make();
	void makeData(size_t& index, const Cell& cell);

	inline void addEvent(EventPtr& ventPtr) {
		if (!_nextEvents) {
			_nextEvents = new std::vector<EventPtr>();
		}

		_nextEvents->push_back(ventPtr);
	}

	void applyDamage(float& valueOut, const float valueWant) {
		valueOut = valueWant;
		_health = _health - valueOut;
		if (_health < 0) {
			valueOut += _health;
			_health = 0.0f;
		}
	}

	inline void setNextPos(const glm::vec3& nextPos) { _nextPos = nextPos; }

private:
	std::vector<EventPtr>* _currentEvents;
	std::vector<EventPtr>* _nextEvents;

	std::vector<BrainPtr> _brainChilds;
	std::vector<EnergyPtr> _energyChilds;
	std::vector<MouthPtr> _mouthChilds;
	std::vector<MoverPtr> _moverChilds;
	
	DnaPtr _dnaPtr;
	float _health;
	glm::vec3 _moveVector;
	glm::vec3 _nextPos;

public:
	static const std::vector<MicrobePtr>& getMicrobes() { return _microbes; }
	static void distMicrobes(MicrobePtr& micribePtr);
	static void updateMicrobes();
	static void clear();
	static void generateMicrobes();
	
private:
	static std::vector<MicrobePtr> _microbes;
	static Point pointsStatic[3];
	static TexCoord texCoordStatic[3];
};

};	// microbe

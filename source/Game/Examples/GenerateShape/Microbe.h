#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Object/Identify.h"
#include "Object/Position.h"
#include "DNA.h"

namespace microbe
{

class Cell;
class Microbe;
class MicrobeShape;

typedef std::shared_ptr<Cell> CellPtr;
typedef std::shared_ptr<Microbe> MicrobePtr;
typedef std::weak_ptr<Microbe> MicrobeWptr;
typedef std::shared_ptr<MicrobeShape> MicrobeShapePtr;

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
	Cell() {}
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
	virtual unsigned short int type() = 0;
	virtual void update() {}

public:
	MicrobeWptr _core;
	float _pos[3];
	float _size;
};

class Microbe final : public Position, public UniqueId
{
public:
	Microbe();
	Microbe(const DnaPtr& DNA);
	Microbe(const std::string& idDNA);
	void update();
	void generate(const MicrobeWptr& microbeWptr);

private:
	std::vector<CellPtr> _childs;
	DnaPtr _dnaPtr;
	MicrobeShapePtr _microbeShapePtr;

public:
	static void updateMicrobes();
	static void clear();
	static void generateMicrobes();
	
private:
	static std::vector<MicrobePtr> _microbes;
};

};	// microbe

//	Brain
//	Mover
//	Mouth
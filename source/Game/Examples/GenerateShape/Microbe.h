#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Object/Identify.h"
#include "Object/Position.h"
#include "Object/Triangle.h"
#include "DNA.h"

namespace microbe
{

class Cell;
class Microbe;

typedef std::shared_ptr<Cell> CellPtr;
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
	Microbe();
	Microbe(const DnaPtr& DNA);
	Microbe(const std::string& idDNA);
	void update();
	void generate(const MicrobeWptr& microbeWptr);

	void make();
	void makeData(size_t& index, const Cell& cell);

private:
	std::vector<CellPtr> _childs;
	DnaPtr _dnaPtr;

public:
	static const std::vector<MicrobePtr>& getMicrobes() { return _microbes; }
	static void updateMicrobes();
	static void clear();
	static void generateMicrobes();
	
private:
	static std::vector<MicrobePtr> _microbes;
	static Point pointsStatic[3];
	static TexCoord texCoordStatic[3];
};

};	// microbe

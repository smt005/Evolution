#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Object/Identify.h"
#include "Object/Position.h"
#include "DNA.h"

namespace microbe
{

class Microbe;

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
	virtual ~Cell() {}
	virtual unsigned short int type() = 0;
	virtual void update() {}

private:
	glm::vec3 pos;
};

typedef std::shared_ptr<Cell> CellPtr;
typedef std::shared_ptr<Microbe> MicrobePtr;

class Microbe final : public Position, public UniqueId
{
public:
	Microbe();
	Microbe(const DnaPtr& DNA);
	Microbe(const std::string& idDNA);
	void update();
	void generate();

private:
	std::vector<CellPtr> _childs;
	DnaPtr _DNA;

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
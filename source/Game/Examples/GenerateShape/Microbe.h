#pragma once

#include <memory>
#include <vector>
#include "Object/Identify.h"
#include "Object/Position.h"

namespace microbe
{

class Microbe;

class Cell
{
public:
	virtual ~Cell() {}
	virtual void update() {}

private:
	float _pos[3];
};

typedef std::shared_ptr<Cell> CellPtr;
typedef std::shared_ptr<Microbe> MicrobePtr;

class Microbe final : public Position, public UniqueId
{
public:
	Microbe();
	void update();
	void generate();

private:
	std::vector<CellPtr> _childs;

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
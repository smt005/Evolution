
#pragma once

class Cell
{
public:
	Cell();
	virtual ~Cell();

	virtual void action() = 0;

protected:
	float _consumption;
};

Cell::Cell()
	: _consumption(0.1f)
{
}

Cell::~Cell()
{
}

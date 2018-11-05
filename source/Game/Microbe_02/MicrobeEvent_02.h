#pragma once

#include "Microbe_02.h"
#include <functional>

/*
NONE,
BRAIN,
ENERGY,
MOUTH,
MOVE
*/

//	DataMoveEvent
class DataMoveEvent : public Microbe_02::Event::Data
{
public:
	Microbe_02::Event::Type getType() override { return Microbe_02::Event::MOVE; }

public:
	glm::vec3 move;
};

//	DataBrainEvent
class DataBrainEvent : public Microbe_02::Event::Data
{
public:
	Microbe_02::Event::Type getType() override { return Microbe_02::Event::BRAIN; }

public:
};


// DataEnergyEvent
class DataEnergyEvent : public Microbe_02::Event::Data
{
public:
	Microbe_02::Event::Type getType() override { return Microbe_02::Event::ENERGY; }

public:
	float needEnergy;
	std::function<void(float)> function;
};

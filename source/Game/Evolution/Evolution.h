
#pragma once

#include "../../Engine/Game.h"

class Mesh;

class Evolution : public Game
{
public:
	Evolution();
	~Evolution();

	void init();
	void update();
	void draw();

private:
	void updateGame();

private:
	Mesh* _mesh;
};
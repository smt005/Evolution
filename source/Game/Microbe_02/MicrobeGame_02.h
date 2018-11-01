#pragma once

#include "../Templates/TemplateGame.h"

class MicrobeGame_02 : public TemplateGame
{
public:
	MicrobeGame_02();
	~MicrobeGame_02();

public:
	std::string getName() override { return "MicrobeGame_02"; }

	void init() override;
	void update() override;
	void draw() override;
};


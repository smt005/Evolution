#pragma once

#include "../Templates/TemplateGame.h"

class NeuronsGame : public TemplateGame
{
public:
	NeuronsGame();
	~NeuronsGame();

public:
	std::string getName() override { return "NeuronsGame"; }

	void init() override;
	void update() override;
	void draw() override;
};

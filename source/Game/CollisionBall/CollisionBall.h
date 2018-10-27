#pragma once

#include "Templates/TemplateGame.h"
#include <string>

class CollisionBall final : public TemplateGame
{
public:
	std::string getName() override { return "CollisionBall"; }

	void init() override;
	void update() override;
};

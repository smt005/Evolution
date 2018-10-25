#pragma once

#include "Templates/TemplateGame.h"
#include <string>

class CollisionBall final : public TemplateGame
{
public:
	CollisionBall();
	~CollisionBall();
	std::string getName() override { return "CollisionBall"; }
};

#pragma once

#include "Templates/TemplateGame.h"
#include <string>
#include <glm/vec3.hpp>

class MoveToTarget final : public TemplateGame
{
private:
	struct VectorShoot {
		glm::vec3 startPos;
		glm::vec3 endPos;
		std::string startNameObject = "start";
		std::string endNameObject = "end";
	};

public:
	std::string getName() override { return "MoveToTarget"; }

	void init() override;
	void update() override;
	void draw() override;

private:
	VectorShoot* _vectorShoot;
};

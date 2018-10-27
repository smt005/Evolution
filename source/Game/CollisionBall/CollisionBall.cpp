#include "CollisionBall.h"
#include "Object/Map.h"
#include "Object/Object.h"

#include <glm/vec3.hpp>
#include <vector>

void CollisionBall::init()
{
	TemplateGame::init();

	//_mapGame ��������� � ������������ ������

	if (_mapGame)
	{
		// ���������� ������� �� �����
		for (float x = -25.0f; x < 25.0f; x += 3.0f) {
			for (float y = -25.0f; y < 25.0f; y += 3.0f) {
				glm::vec3 pos(x, y, 1.0f);
				Object& object = _mapGame->addObjectToPos("Sphere_01", pos); // �������� ������ � �������
				object.tag = 123;	// ��� ���� ����� �������� �� ������ ��������
			}
		}
		
	}
}

void CollisionBall::update()
{
	TemplateGame::update();

	// ������ �������� �����
	std::vector<Object*>& objects = _mapGame->objects;
	for (Object* object : objects)
	{
		if (!object) continue;
		if (object->tag != 123) continue;

		glm::vec3 pos = object->getPos();

		//...
	}
}

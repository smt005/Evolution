#include "CollisionBall.h"
#include "Object/Map.h"
#include "ObjectMove.h"
#include "Common/Help.h"
#include "Callback/Callback.h"
#include "Core.h"

#include <glm/vec3.hpp>
#include <vector>

void CollisionBall::init()
{
	TemplateGame::init();

	//_mapGame ��������� � ������������ ������

	if (_mapGame)
	{
		// ���������� ������� �� �����
		for (float x = -15.0f; x < 15.0f; x += 2.5f) {
			for (float y = -15.0f; y < 15.0f; y += 2.5f) {
				
				// ���������� �������� �������
				//glm::vec3 pos(x, y, 1.0f);
				//Object& object = _mapGame->addObjectToPos("Sphere_01", pos); // �������� ������ � �������

				ObjectMove* objectMove = new ObjectMove();
				objectMove->set("", "Sphere_01", glm::vec3(x, y, 1.0f));
				objectMove->tag = 123;	// ��� ���� ����� �������� �� ������ ��������

				objectMove->vectorMove = glm::vec3(
					help::random_f(-0.91f, 0.91f),
					help::random_f(-0.91f, 0.91f),
					0.0f );

				_mapGame->addObject(objectMove);
			}
		}
		
	}
}

void CollisionBall::update()
{
	TemplateGame::update();

	// ������ �������� �����
	std::vector<Object*>& balls = _mapGame->objects;

	//---
	size_t ballCount = balls.size();

	for (int i = 0; i < ballCount; i++)
	{
		if (!balls[i]) continue;
		if (balls[i]->tag != 123) continue;
		ObjectMove& object = *static_cast<ObjectMove*>(balls[i]);

		for (int j = i + 1; j < ballCount; j++)
		{
			if (!balls[j]) continue;
			if (balls[j]->tag != 123) continue;
			ObjectMove& objectTrget = *static_cast<ObjectMove*>(balls[j]);

			if (object.colliding(objectTrget)) {
				object.resolveCollision(objectTrget);
			}
		}
	}

	//---
	for (Object* objectPtr : balls)
	{
		if (!objectPtr) continue;
		if (objectPtr->tag != 123) continue;

		ObjectMove& object = *static_cast<ObjectMove*>(objectPtr);

		glm::vec3 pos = object.getPos();
		glm::vec3 move = object.vectorMove;

		pos += move;

		object.setPos(pos);
	}
}

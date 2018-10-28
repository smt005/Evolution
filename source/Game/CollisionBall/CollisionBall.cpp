#include "CollisionBall.h"
#include "Object/Map.h"
#include "ObjectMove.h"
#include "Common/Help.h"
#include "Callback/Callback.h"

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
				
				// ���������� �������� �������
				//glm::vec3 pos(x, y, 1.0f);
				//Object& object = _mapGame->addObjectToPos("Sphere_01", pos); // �������� ������ � �������

				ObjectMove* objectMove = new ObjectMove();
				objectMove->set("", "Sphere_01", glm::vec3(x, y, 1.0f));
				objectMove->tag = 123;	// ��� ���� ����� �������� �� ������ ��������

				objectMove->vectorMove = glm::vec3(
					help::random_f(-0.005f, 0.005f),
					help::random_f(-0.005f, 0.005f),
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
	std::vector<Object*>& objects = _mapGame->objects;
	for (Object* objectPtr : objects)
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

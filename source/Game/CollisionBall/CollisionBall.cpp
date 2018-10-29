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

	//_mapGame находится в родительском классе

	if (_mapGame)
	{
		// Добавление объекта на карту
		for (float x = -15.0f; x < 15.0f; x += 2.5f) {
			for (float y = -15.0f; y < 15.0f; y += 2.5f) {
				
				// Добавление обычного объекта
				//glm::vec3 pos(x, y, 1.0f);
				//Object& object = _mapGame->addObjectToPos("Sphere_01", pos); // Название модели и позиция

				ObjectMove* objectMove = new ObjectMove();
				objectMove->set("", "Sphere_01", glm::vec3(x, y, 1.0f));
				objectMove->tag = 123;	// Для того чтобы отличить от других объектов

				objectMove->vectorMove = glm::vec3(
					help::random_f(-0.0001f, 0.0001f),
					help::random_f(-0.0001f, 0.0001f),
					0.0f );

				_mapGame->addObject(objectMove);
			}
		}

		// Callback
		_callback = new Engine::Callback(Engine::CallbackType::RELEASE_TAP, [this](const Engine::CallbackEventPtr& callbackEventPtr) {
			Engine::TapCallbackEvent* releaseKeyEvent = (Engine::TapCallbackEvent*)callbackEventPtr->get();
			Engine::VirtualTap tap = releaseKeyEvent->getId();

			if (tap != Engine::VirtualTap::LEFT) {
				return;
			}

			ObjectMove* objectMove = new ObjectMove();
			objectMove->set("", "Sphere_01", glm::vec3(-40.0f, 0.0f, 1.0f));
			objectMove->tag = 123;	// Для того чтобы отличить от других объектов

			objectMove->vectorMove = glm::vec3(	0.2f + help::random_f(-0.05f, 0.05f),
												help::random_f(-0.05f, 0.05f),
												0.0f);

			_mapGame->addObject(objectMove);
		});
	}
}

void CollisionBall::update()
{
	TemplateGame::update();

	// Массив объектов карты
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

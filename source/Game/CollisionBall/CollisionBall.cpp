#include "CollisionBall.h"
#include "Object/Map.h"
#include "Object/Line.h"
#include "ObjectMove.h"
#include "Common/Help.h"
#include "Callback/Callback.h"
#include "Draw/Camera.h"
#include "Core.h"
#include "Draw/DrawLine.h"

#include <glm/mat4x4.hpp>
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

		{

			Object& object = _mapGame->addObjectToPos("Cursor_red");
			object.setName("start");
			object.tag = 1;
		}
		{
			Object& object = _mapGame->addObjectToPos("Cursor_red");
			object.setName("end");
			object.tag = 1;
		}

		// Callback
		if (_callback)
		{
			_callback->add(Engine::CallbackType::RELEASE_TAP, [this](const Engine::CallbackEventPtr& callbackEventPtr) {
				Engine::TapCallbackEvent* releaseKeyEvent = (Engine::TapCallbackEvent*)callbackEventPtr->get();
				Engine::VirtualTap tap = releaseKeyEvent->getId();

				if (tap != Engine::VirtualTap::LEFT) {
					return;
				}

				if (!_vectorShoot) {
					return;
				}

				glm::vec3 vec = _vectorShoot->endPos - _vectorShoot->startPos;
				vec *= 0.01f;

				ObjectMove* objectMove = new ObjectMove();
				objectMove->tag = 123;	// Для того чтобы отличить от других объектов

				_vectorShoot->startPos.z = 1.0f;
				objectMove->set("", "Sphere_01", _vectorShoot->startPos);

				//objectMove->vectorMove = glm::vec3(	0.2f + help::random_f(-0.05f, 0.05f),
					//								help::random_f(-0.05f, 0.05f),
						//							0.0f);


				vec.z = 0.0f;
				objectMove->vectorMove = glm::vec3(vec);

				_mapGame->addObject(objectMove);

				delete _vectorShoot;
				_vectorShoot = nullptr;
			});

			_callback->add(Engine::CallbackType::PRESS_TAP, [this](const Engine::CallbackEventPtr& callbackEventPtr) {
				if (!_vectorShoot) {
					_vectorShoot = new VectorShoot();
					_vectorShoot->startPos = Camera::current.corsorCoord();
					_vectorShoot->endPos = Camera::current.corsorCoord();
				}
			});

			_callback->add(Engine::CallbackType::MOVE, [this](const Engine::CallbackEventPtr& callbackEventPtr) {
				if (_mapGame && _vectorShoot) {
					_vectorShoot->endPos = Camera::current.corsorCoord();
					Object& object = help::find(_mapGame->objects, _vectorShoot->endNameObject);
					object.setPos(_vectorShoot->endPos);
				}
			});
		}
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

void CollisionBall::draw()
{
	TemplateGame::draw();

	if (!_vectorShoot) return;

	draw::DrawLine::prepare();
	
	float points[6] = { _vectorShoot->startPos.x, _vectorShoot->startPos.y, 0.0f, _vectorShoot->endPos.x, _vectorShoot->endPos.y, 0.0f };
	
	Line line(points, 2, Line::LINE);
	line.setLineWidth(5.0f);
	line.color = Color::RED;
	line.color.setAlpha(2.5);

	draw::DrawLine::draw(line);
}

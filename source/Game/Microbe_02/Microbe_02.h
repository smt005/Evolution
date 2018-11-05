#pragma once

#include "Object/Triangle.h"
#include "Physic/PhysicCircle2D.h"
#include "Object/Identify.h"
#include "Common/ItemsClass.h"
#include <memory>
#include <vector>

class Microbe_02;
typedef std::shared_ptr<Microbe_02> Microbe_02Ptr;
class CellEnergy;
typedef std::shared_ptr<CellEnergy> CellEnergyPtr;
class CellMove;
typedef std::shared_ptr<CellMove> CellMovePtr;
class CellMouth;
typedef std::shared_ptr<CellMouth> CellMouthPtr;
class CellBrain;
typedef std::shared_ptr<CellBrain> CellBrainPtr;

class DataMoveEvent;
class DataEnergyEvent;

class Microbe_02 final : public ItemsClass <Microbe_02>, public UniqueId
{
public:
	class Event final
	{
	public:
		enum
		{
			NONE,
			BRAIN,
			ENERGY,
			MOUTH,
			MOVE
		};
		typedef unsigned short int Type;

		//	Data
		class Data
		{
		public:
			virtual Type getType() = 0;
		};

		typedef std::shared_ptr<Data> DataPtr;

		//	Event
		Event() : 
			_data(nullptr) {}

		Event(Data* data) : _data(data) {}

		inline Type getType() {
			if (_data) {
				return _data->getType();
			}
			return NONE;
		}

		template <class EventDataT>
		inline EventDataT* getData() { return static_cast<EventDataT*>(_data.get()); }

	private:
		DataPtr _data;
	};

	Microbe_02();
	~Microbe_02();
	void init(const glm::vec3& pos);
	void update();
	glm::mat4x4 getMatrix() override;
	TrianglePtr getModel() {
		return _triangle;
	}
	void kill() {
		_live = nullptr;
	}

	//---
	
	void applyEvents();
	void addEvent(Event& event) {
		_events.push_back(event);
	}

	void applyEvent(DataMoveEvent& data);
	void applyEvent(DataEnergyEvent& data);

public:
	CellEnergyPtr	cellEnergy;
	CellMovePtr		cellMove;
	CellMouthPtr	cellMouth;
	CellBrainPtr	cellBrain;

private:
public:
	PhysicCircle2DPtr	_physic;
	TrianglePtr			_triangle;
	std::shared_ptr<float> _live;
	std::vector<Event> _events;

public:
	static void generate(const unsigned int count);
};

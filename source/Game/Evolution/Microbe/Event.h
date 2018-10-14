#pragma once

#include <functional>

namespace microbe
{

class Microbe;
class Event;

typedef std::shared_ptr<Event> EventPtr;
typedef std::shared_ptr<Microbe> MicrobePtr;

class Event
{
public:
	typedef unsigned short int Type;
	typedef std::function<void(bool)> Callback;
	enum
	{
		NONE,
		MOVE,
		ENERGY_LOAD,
		ENERGY_GET,
		EAT
	};

public:
	virtual ~Event() {}
	inline virtual const Type getType() const = 0;
	inline Event* getPoint() { return this; }

};


// Команда на движение
class EventMove final : public Event
{
public:
	EventMove() : _moverId(-1), _state(false), _callback(0) { }
	EventMove(const short int moverId, const bool state, const Callback callback) : _moverId(moverId), _state(state), _callback(callback) { }
	inline const Type getType() const override { return MOVE; }
	inline void apply() {
		if (_callback) {
			_callback(true);
		}
	}
	
	inline const short int getMoverId() const { return _moverId; }
	inline const bool getState() const { return _state; }
	inline const Callback getCallback() const { return _callback; }

private:
	short int _moverId = -1;
	bool _state;
	Callback _callback;
};

// Заполнение контейнера энеогией
class EventEnergyLoad final : public Event
{
public:
	EventEnergyLoad() {}
	EventEnergyLoad(const float valueLoad, Callback callback) : _valueLoad(valueLoad) { }
	inline const Type getType() const override { return ENERGY_LOAD; }
	
	void apply() {
		if (_callback) {
			_callback(true);
		}
	}

	inline const float getValueLoad() const { return _valueLoad; }
	inline const Callback getCallback() const { return _callback; }

private:
	float _valueLoad;
	Callback _callback;
};

//
class EventEnergyGet final : public Event
{
public:
	EventEnergyGet() {}
	EventEnergyGet(const float valueWant, Callback callback) : _valueWant(valueWant), _callback(callback){ }
	inline const Type getType() const override { return ENERGY_GET; }

	void apply() {
		if (_callback) {
			_callback(true);
		}
	}

	inline const float getValueWant() const { return _valueWant; }
	inline const Callback getCallback() const { return _callback; }

private:
	float _valueWant;
	Callback _callback;
};

//
class EventEat final : public Event
{
public:
	EventEat() {}
	EventEat(MicrobePtr target, const float valueDamage, Callback callback);
	inline const Type getType() const override { return EAT; }

	void apply() {
		if (_callback) {
			_callback(true);
		}
	}

	inline const float getValueDamage() const { return _valueDamage; }
	inline MicrobePtr getTarget() const { return _target; }
	inline const Callback getCallback() const { return _callback; }

private:
	float _valueDamage;
	MicrobePtr _target;
	Callback _callback;
};

};	// microbe
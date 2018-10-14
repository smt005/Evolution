
#include "Event.h"
#include "Microbe.h"

using namespace microbe;

EventEat::EventEat(MicrobePtr target, const float valueDamage, Callback callback) : _target(target), _valueDamage(valueDamage), _callback(callback) { }
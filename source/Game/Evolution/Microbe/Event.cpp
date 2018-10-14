
#include "Event.h"
#include "Microbe.h"

using namespace microbe;

EventEat::EventEat(MicrobePtr target, Callback callback) : _target(target), _callback(callback) { }
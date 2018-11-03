
#include "Microbe_02.h"

//	DataMoveEvent
class DataMoveEvent : public Microbe_02::Event::Data
{
public:
	Microbe_02::Event::Type getType() override { return Microbe_02::Event::MOVE; }

public:
	glm::vec3 move;
};

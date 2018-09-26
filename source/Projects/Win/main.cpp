
#include "Engine.h"
#include "Evolution/Evolution.h"

int main(int argc, char **argv)
{
	return Core:: Engine::execution(new Evolution());
}

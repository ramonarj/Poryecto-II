#include "Slide.h"
#include "Game.h"


Slide::Slide()
{
}


Slide::~Slide()
{
}

bool Slide::interact(Entity * e)
{
	Game::Instance()->getStateMachine()->pushState(SlidingPuzzle::Instance());
	return true;
}

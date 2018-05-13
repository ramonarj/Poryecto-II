#include "Slide.h"
#include "Game.h"


Slide::Slide()
{
}


Slide::~Slide()
{
}

void Slide::interact(Entity * e)
{
	Game::Instance()->getStateMachine()->pushState(SlidingPuzzle::Instance());
}

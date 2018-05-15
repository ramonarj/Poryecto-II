#include "SlidingPuzzleItem.h"



SlidingPuzzleItem::SlidingPuzzleItem(std::string interactMessage) : Interactible(interactMessage)
{
}


SlidingPuzzleItem::~SlidingPuzzleItem()
{
}

bool SlidingPuzzleItem::interact(Entity* e) {
	Game::Instance()->getStateMachine()->pushState(SlidingPuzzle::Instance());
	return true;
}
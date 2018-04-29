#pragma once
#include "Interactible.h"
#include "SlidingPuzzle.h"
class SlidingPuzzleItem : public Interactible
{
public:
	SlidingPuzzleItem(std::string interactMessage = "");
	~SlidingPuzzleItem();

	virtual void interact(Entity* e);

};


#pragma once
#include "Interactible.h"
#include "SlidingPuzzle.h"

class Slide : public Interactible
{
public:
	Slide();
	~Slide();

	virtual void interact(Entity* e);
};


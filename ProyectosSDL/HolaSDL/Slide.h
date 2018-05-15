#pragma once
#include "Interactible.h"
#include "SlidingPuzzle.h"

class Slide : public Interactible
{
public:
	Slide();
	~Slide();

	virtual bool interact(Entity* e);
};


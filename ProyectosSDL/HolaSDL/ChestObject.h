#pragma once
#include "Interactible.h"
class ChestObject :
	public Interactible
{
public:
	ChestObject();
	virtual ~ChestObject();
	virtual void interact(Entity* e) {};
};


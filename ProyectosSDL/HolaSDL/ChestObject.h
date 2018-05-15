#pragma once
#include "Interactible.h"
class ChestObject :
	public Interactible
{
public:
	ChestObject();
	virtual ~ChestObject();
	virtual bool interact(Entity* e) { return true; };
};


#pragma once
#include "Interactible.h"
class CraftingTable :
	public Interactible
{
public:
	CraftingTable();
	virtual ~CraftingTable();
	virtual void interact(Entity* e) {};
};


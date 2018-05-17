#pragma once
#include "Interactible.h"
#include "checkML.h"


class CraftingTable :
	public Interactible
{
public:
	CraftingTable();
	virtual ~CraftingTable();
	virtual bool interact(Entity* e) { return true; };
};


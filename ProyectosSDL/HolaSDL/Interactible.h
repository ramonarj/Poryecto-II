#pragma once

#include "Component.h"
class ItemContainer;
class Interactible :
	public Component
{
public:
	Interactible();
	~Interactible();
	virtual void interact(Entity* e) = 0; // M�todo abstracto de la interacci�n
};


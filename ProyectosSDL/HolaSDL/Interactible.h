#pragma once
#include "Component.h"
class ItemContainer;
class Interactible :
	public Component
{
public:
	Interactible();
	~Interactible();
	virtual void interact(Entity* e, ItemContainer* ic) = 0; // Método abstracto de la interacción
};


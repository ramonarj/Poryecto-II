#pragma once
#include "Component.h"
class Interactible :
	public Component
{
public:
	Interactible();
	~Interactible();
	virtual void interact() = 0; // M�todo abstracto de la interacci�n
};


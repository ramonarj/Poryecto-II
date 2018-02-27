#pragma once
#include "LogicComponent.h"
class Interactible :
	public LogicComponent
{
public:
	Interactible();
	~Interactible();
	virtual void interact() = 0; // Método abstracto de la interacción
};


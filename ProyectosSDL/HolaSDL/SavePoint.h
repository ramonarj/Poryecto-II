#pragma once
#include "Interactible.h"
#include "PlayState.h"
class SavePoint :public Interactible
{
public:
	SavePoint();
	~SavePoint();

	virtual void interact(Entity* e);
};


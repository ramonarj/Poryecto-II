#pragma once
#include "Interactible.h"
#include "PlayState.h"
#include "checkML.h"


class SavePoint :public Interactible
{
public:
	SavePoint();
	~SavePoint();

	virtual bool interact(Entity* e);
};


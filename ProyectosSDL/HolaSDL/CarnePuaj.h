#pragma once
#include "Interactible.h"
#include "Inventory.h"
class CarnePuaj : public Interactible
{
public:
	CarnePuaj(std::string interactMessage = "");
	~CarnePuaj();
	virtual void interact(Entity* e);
	virtual void update(Entity* e, Uint32 time);
private:
	bool acid_;

	Entity* player = nullptr;
	Inventory* inventory = nullptr;
};


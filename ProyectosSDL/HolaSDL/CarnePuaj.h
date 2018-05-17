#pragma once
#include "Interactible.h"
#include "Inventory.h"
#include "checkML.h"


class CarnePuaj : public Interactible
{
public:
	CarnePuaj(std::string interactMessage = "");
	~CarnePuaj();
	virtual bool interact(Entity* e);
	virtual void update(Entity* e, Uint32 time);

	bool playerCanMove(Entity* e);
private:
	bool acid_;

	Entity* player = nullptr;
	Inventory* inventory = nullptr;
	Vector2D playerDir;
};


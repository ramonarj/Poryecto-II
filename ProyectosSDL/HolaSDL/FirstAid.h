#pragma once
#include "Item.h"
#include "Player.h"

class FirstAid : public Item
{
public:
	FirstAid();
	virtual ~FirstAid();
	virtual void update(Entity* e, Uint32 time);
	virtual void useItem(Entity* e);
private:
	int lifeFilling = 3;
};


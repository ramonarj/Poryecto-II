#pragma once
#include "Item.h"
#include "Player.h"

class FirstAid : public Item
{
public:
	FirstAid(const string& filename);
	virtual ~FirstAid();
	virtual void update(Entity* e, Uint32 time);
	virtual void use(Entity* e);
private:
	int lifeFilling = 3;
};


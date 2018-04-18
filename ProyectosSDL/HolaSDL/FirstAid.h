#pragma once
#include "Item.h"
#include "Player.h"

class FirstAid : public Item
{
public:
	FirstAid(const string& filename);
	virtual ~FirstAid();
	virtual void use(Entity* e, Entity* item);
private:
	int lifeFilling = 3;
};


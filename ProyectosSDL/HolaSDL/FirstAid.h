#pragma once
#include "Item.h"
#include "Player.h"
#include "checkML.h"


class FirstAid : public Item
{
public:
	FirstAid(const string& filename, std::string interactMessage = "");
	virtual ~FirstAid();
	virtual void use(Entity* e, Entity* item);
private:
	int lifeFilling = 3;
};


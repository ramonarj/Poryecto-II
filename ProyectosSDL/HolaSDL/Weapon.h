#pragma once
#include "Item.h"
class Weapon : public Item
{
public:
	Weapon(ItemType type);
	~Weapon();
	virtual void update();
	void weaponType(ItemType type);
private:
	int damage = 1;
	int hits;
};


#pragma once
#include "Item.h"

class Key : public Item
{
public:
	Key(const string& filename) : Item(ItemType::KEY, filename) {};
	~Key() {};

	//virtual void use(Entity* e) {};
	void setDoorId(int id) { doorId = id; };
	const int getDoorId() const { return doorId; };
private:
	int doorId;
};


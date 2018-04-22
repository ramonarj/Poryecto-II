#pragma once
#include "Item.h"

class Key : public Item
{
public:
	Key(const string& filename, std::string interactMessage = "") : Item(ItemType::KEY, filename, interactMessage) {};
	~Key() {};

	//virtual void use(Entity* e) {};
	void setDoorId(int id) { doorId = id; };
	const int getDoorId() const { return doorId; };
	void load(int numDoor);
private:
	int doorId;
};


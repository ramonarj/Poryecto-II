#pragma once
#include "Item.h"
#include "checkML.h"



class Key : public Item
{
public:
	Key(const string& filename, std::string interactMessage = "") : Item(ItemType::KEY, filename, interactMessage) {};
	~Key() {};

	//virtual void use(Entity* e) {};
	void setDoorId(int id) { doorId = id; };
	int getDoorId() { return doorId; };

	void setKeyName(string name) { keyName_ = name; };
	string getKeyName() { return keyName_; };

	void load(int numDoor, string keyName);

private:
	int doorId;
	string keyName_;
	string initialDescription_;
};


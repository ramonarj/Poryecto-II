#pragma once

#include "checkML.h"
#include "Interactible.h"
#include <list>
#include "Inventory.h"

class Door : public Interactible
{
public:
	Door(Entity* thisDoor);
	~Door();

	virtual void interact(Entity* e);

	void load(int numero, string ori, int numKey, int needKey, int collidableDoor);

	int getDoorNum() { return doorNum_; };
	int getNumKey() { return numKey_; };
	string getOri() { return ori_; };

	bool canTeleport();
	bool getNeedKey();
	void setNeedKey();
	void openDoor();
	void keyFalse();
	bool isCollidable();

private:
	list<Entity*> doors;
	Entity* player;
	Entity* inventory;
	ItemContainer* compContainer;
	Inventory* compInvent;
	Entity* itemKey;
	Entity* thisDoor_;

	int doorNum_;
	string ori_;
	int numKey_;
	bool needKey_;
	bool collidableDoor_;
};


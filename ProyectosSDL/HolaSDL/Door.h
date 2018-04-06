#pragma once
#include "Interactible.h"
#include <list>
#include "Inventory.h"

class Door : public Interactible
{
public:
	Door();
	~Door();

	virtual void interact(Entity* e);

	void load(int numero, string ori, int numKey, int needKey);

	int getDoorNum() { return doorNum_; };
	string getOri() { return ori_; };

	bool canTeleport();
	void setNeedKey();
	void keyFalse();

private:
	list<Entity*> doors;
	Entity* player;
	Entity* inventory;
	ItemContainer* compContainer;
	Inventory* compInvent;
	Entity* itemKey;

	int doorNum_;
	string ori_;
	int numKey_;
	bool needKey_;
};


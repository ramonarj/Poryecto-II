#pragma once

#include "checkML.h"
#include "Interactible.h"
#include <list>
#include "Inventory.h"
#include "MessageRenderer.h"
#include "MessageTimer.h"

class Door : public Interactible
{
public:
	Door(Entity* thisDoor);
	~Door();

	virtual void interact(Entity* e);

	void load(int numero, string ori, int needKey, int collidableDoor, string zoneName, bool ancha);

	int getDoorNum() { return doorNum_; };
	string getOri() { return ori_; };
	bool getAncha() { return ancha_; };
	string getZoneName() { return zoneName_; };

	bool canTeleport();
	void teleport();
	bool getNeedKey();
	void setNeedKey();
	void openDoor();
	void keyFalse();
	bool isCollidable();

	virtual void update(Entity* e, Uint32 time);
	virtual void saveToFile(Entity * o);
	virtual void loadToFile(Entity * o);

private:
	list<Entity*> doors;
	Entity* player;
	Entity* inventory;
	ItemContainer* compContainer;
	Inventory* compInvent;
	Entity* itemKey;
	Entity* thisDoor_;

	MessageRenderer* messageRenderer;
	MessageTimer* messageTimer;

	int doorNum_;
	string ori_;
	string zoneName_;
	bool needKey_;
	bool collidableDoor_;
	bool messageChanged_;
	bool ancha_ = false;
};


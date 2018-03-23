#pragma once
#include "Interactible.h"
#include <list>
class Door : public Interactible
{
public:
	Door();
	~Door();

	virtual void interact(Entity* e);

	void load(int numero, string ori);

	int getDoorNum() { return doorNum_; };
	string getOri() { return ori_; };

private:
	list<Entity*> doors;
	Entity* player;

	int doorNum_;
	string ori_;
};


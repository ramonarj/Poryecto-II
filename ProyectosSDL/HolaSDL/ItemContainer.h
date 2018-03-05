#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "Resources.h"
#include "Weapon.h"
#include "InsulationTape.h"

using namespace std;

struct coord {
	int x;
	int y;
};

class ItemContainer : public Component
{
public:
	ItemContainer(int tam);
	~ItemContainer();

protected:
	int tam;
	vector<Entity*> inventory;
	vector<coord> ObjPos;

public:

	//ADD AND DELETE OBJECTS TO THE INVENTORY
	virtual void addItem(Entity* item) = 0;
	void DeleteItem(int pos);
	void ClearInventory();

	//CHECK METHODS
	virtual bool checkItem(Entity* item) = 0;
	virtual Entity* ItemInPosition(int pos) = 0;
	//It returns false if the inventory isn't full
	bool fullInventory();
	bool empty();
	//GETS
	int getItemPosX(int i) { return ObjPos[i].x; };
	int getItemPosY(int i) { return ObjPos[i].y; };

};


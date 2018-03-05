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
	ItemContainer();
	~ItemContainer();

protected:
	
	static const int InvTam = 4;
	static const int chestTam = 10;
	bool clicked = false;
	int slotClicked;
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
	virtual bool fullInventory() = 0;
	bool empty();
	//GETS
	int getItemPosX(int i) { return ObjPos[i].x; };
	int getItemPosY(int i) { return ObjPos[i].y; };

};


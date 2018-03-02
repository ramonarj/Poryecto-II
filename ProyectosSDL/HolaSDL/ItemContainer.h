#pragma once
#include "LogicComponent.h"
#include <vector>
#include "Item.h"
#include "Texture.h"

using namespace std;

class ItemContainer : public LogicComponent
{
public:
	ItemContainer(int tam);
	~ItemContainer();

protected:
	int tam;
	vector<Item*> inventory;

public:

	//ADD AND DELETE OBJECTS TO THE INVENTORY
	virtual void addItem(Item* item) = 0;
	void DeleteItem(int pos);
	void ClearInventory();

	//CHECK METHODS
	virtual bool checkItem(Item* item) = 0;
	virtual Item* ItemInPosition(int pos) = 0;
	//It returns false if the inventory isn't full
	bool fullInventory();
	bool empty();

};

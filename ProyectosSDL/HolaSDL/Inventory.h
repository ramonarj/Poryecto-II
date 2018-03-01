#pragma once
#include "LogicComponent.h"
#include <vector>
#include "Item.h"
#include "Entity.h"

using namespace std;

class Inventory : public  Entity
{
public:
	Inventory(SDLGame* game, int tam);
	~Inventory();

protected:
	int tam;
	bool debug;
	vector<Item*> inventory;

public:
	//DEBUG METHODS
	void Debug_Mode_On() { debug = true; };
	void Debug_Mode_Off() { debug = false; };

	//ADD AND DELETE OBJECTS TO THE INVENTORY
	void addItem(Item* item);
	void DeleteItem(int pos);
	void ClearInventory();

	//CHECK METHODS
	bool checkItem(Item* item);
	Item* ItemInPosition(int pos);
	//It returns false if the inventory isn't full
	bool fullInventory();
	bool empty();
	


	
};




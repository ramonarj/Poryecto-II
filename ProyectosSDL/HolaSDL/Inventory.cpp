#include "Inventory.h"


Inventory::Inventory(SDLGame* game, int tam) : Entity(game)
{
	this->tam = tam;
	this->debug = false;
}

Inventory::~Inventory()
{
}
//ADD ITEM TO INVENTORY
void Inventory::addItem(Item * item)
{
	if (!fullInventory()) { inventory.push_back(item); }
}
//DELETE ITEM FROM SELECTED POSITION
void Inventory::DeleteItem(int pos)
{
	if (!empty()) { inventory.erase(inventory.begin() + pos); }
}
//MAKE AN EMPTY INVENTORY
void Inventory::ClearInventory()
{
	while (!empty())
	{
		inventory.erase(inventory.begin());
	}
}
//CHECK IF ITEM "item" IS ON THE INVENTORY
bool Inventory::checkItem(Item* item)
{
	int i = 0;
	bool found = false;

	while (!found && i < inventory.size() && !empty())
	{
		if (ItemInPosition(i) == item) { found = true; }
	}
	return found;
}
//CHECK WHAT ITEM IS ON THE INDICATED POSITION
Item* Inventory::ItemInPosition(int pos)
{
	if (pos < inventory.size() && !empty()) { return inventory[pos]; }
	else return nullptr;
}
//CHECK IF INVENTORY IS FULL
bool Inventory::fullInventory()
{
	if (inventory.size() >= tam) { return true; }
	else return false;
}
//CHECK IF INVENTORY IS EMPTY
bool Inventory::empty()
{
	if (inventory.empty()) { return true; }
	else return false;
}



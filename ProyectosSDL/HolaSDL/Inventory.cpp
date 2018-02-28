#include "Inventory.h"


Inventory::Inventory(SDLGame* game, int tam) : Entity(game)
{
	this->tam = tam;
	this->debug = false;
}

Inventory::~Inventory()
{
}

void Inventory::addItem(Item * item)
{
	if (!fullInventory()) { inventory.push_back(item); }
}

void Inventory::DeleteItem(int pos)
{
	if (!empty()) { inventory.erase(inventory.begin() + pos); }
}

void Inventory::ClearInventory()
{
	while (!empty())
	{
		inventory.erase(inventory.begin());
	}
}

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

Item* Inventory::ItemInPosition(int pos)
{
	if (pos < inventory.size() && !empty()) { return inventory[pos]; }
	else return nullptr;
}

bool Inventory::fullInventory()
{
	if (inventory.size() >= tam) { return true; }
	else return false;
}

bool Inventory::empty()
{
	if (inventory.empty()) { return true; }
	else return false;
}



#include "ItemContainer.h"



ItemContainer::ItemContainer()
{
}


ItemContainer::~ItemContainer()
{
}

//DELETE ITEM FROM SELECTED POSITION
void ItemContainer::DeleteItem(int pos)
{
	if (!empty()) { inventory.erase(inventory.begin() + pos); }
}
//MAKE AN EMPTY INVENTORY
void ItemContainer::ClearInventory()
{
	while (!empty())
	{
		inventory.erase(inventory.begin());
	}
}

//CHECK IF INVENTORY IS EMPTY
bool ItemContainer::empty()
{
	if (inventory.empty()) { return true; }
	else return false;
}

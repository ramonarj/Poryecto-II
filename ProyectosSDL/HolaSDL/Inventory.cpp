#include "Inventory.h"


Inventory::Inventory(int tam) : ItemContainer(tam)
{
	debug = false;
	equiped = nullptr;
}

Inventory::~Inventory()
{
}

void Inventory::update()
{
	handleInput();
	render();
}
void Inventory::handleInput()
{
}

void Inventory::render()
{
	
}

void Inventory::addItem(Item * item)
{
	if (equiped == nullptr)
	{
		if (Weapon* wep = dynamic_cast<Weapon*>(item))
			equiped = wep;
	}
	else if (!fullInventory()) { inventory.push_back(item); }
}

//CHECK IF ITEM "item" IS ON THE INVENTORY
bool Inventory::checkItem(Item * item)
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
Item * Inventory::ItemInPosition(int pos)
{
	if (pos < inventory.size() && !empty()) { return inventory[pos]; }
	else return nullptr;
}

void Inventory::equipWeapon(int pos)
{
	if(Weapon* wep = dynamic_cast<Weapon*>(inventory[pos])) {

		if (equiped != nullptr) {
			Item* aux = currentWeapon();
			equiped = wep;
			this->DeleteItem(pos);
			addItem(aux);
		}
		else
		{
			equiped = wep;
			this->DeleteItem(pos);	
		}
		
	}
}

Weapon * Inventory::currentWeapon()
{
	return equiped;
}





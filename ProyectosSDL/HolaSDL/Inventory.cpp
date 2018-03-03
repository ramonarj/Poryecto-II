#include "Inventory.h"


Inventory::Inventory(int tam, Texture* tex) : ItemContainer(tam, tex)
{
	debug = false;
	equiped = nullptr;
}

Inventory::~Inventory()
{
}

void Inventory::update(Entity* e, Uint32 time)
{
	//render(e, time);
}

void Inventory::handleInput(Entity* e, Uint32 time, const SDL_Event& event)
{
}

void Inventory::render(Entity* e, Uint32 time)
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = 600;
	dest.h = 600;
	texture->render(e->getGame()->getRenderer(), dest);
	//SDL_RenderPresent(e->getGame()->getRenderer());
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





#include "Inventory.h"


Inventory::Inventory(int tam) : ItemContainer(tam)
{
	debug = false;
	equiped = nullptr;

	coord pos;
	pos.x = 32; pos.y = 306;
	for (int i = 0; i < tam; i++)
	{
		ObjPos.push_back(pos);
		pos.x += 61;
	}
}

Inventory::~Inventory()
{
}

void Inventory::update(Entity* e, Uint32 time)
{
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
	e->getGame()->getResources()->getImageTexture(Resources::Inventory)->render(e->getGame()->getRenderer(), dest);

	for (int i = 0; i < inventory.size(); i++)
	{
		SDL_Rect DestRect = { getItemPosX(i), getItemPosY(i), 50, 50 };

		if(inventory[i]->getComponent<InsulationTape>())
		{
			inventory[i]->getGame()->getResources()->getImageTexture(Resources::PruebaMedicKit)->render(e->getGame()->getRenderer(), DestRect);
		}
		else if (inventory[i]->getComponent<Weapon>())
		{
			if(inventory[i]->getComponent<Weapon>()->getType() == ItemType::Stick)
			inventory[i]->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
		}
	}
}

void Inventory::addItem(Entity * item)
{
	bool equip = false;
	if (equiped == nullptr)
	{
		Weapon* wep = item->getComponent<Weapon>();
		if (wep != nullptr) {
			equiped = item;
			equip = true;
		}
	}
	if (!fullInventory() && !equip) { inventory.push_back(item); }
}

//CHECK IF ITEM "item" IS ON THE INVENTORY
bool Inventory::checkItem(Entity * item)
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
Entity * Inventory::ItemInPosition(int pos)
{
	if (pos < inventory.size() && !empty()) { return inventory[pos]; }
	else return nullptr;
}

void Inventory::equipWeapon(int pos)
{
	if(inventory[pos]->getComponent<Weapon>()) {

		if (equiped != nullptr) {
			Entity* aux = currentWeapon();
			equiped = inventory[pos];
			this->DeleteItem(pos);
			addItem(aux);
		}
		else
		{
			equiped = inventory[pos];
			this->DeleteItem(pos);	
		}
		
	}
}

Entity * Inventory::currentWeapon()
{
	return equiped;
}





#include "ItemContainer.h"
#include "Game.h"


ItemContainer::ItemContainer()
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResourceManager();
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

void ItemContainer::renderItem(int i, Entity * e, SDL_Rect DestRect)
{
	if (inventory[i]->getComponent<InsulationTape>())
	{
		resource->getTexture("insulationTape")->render(pRenderer, DestRect);
	}
	else if (inventory[i]->getComponent<Weapon>())
	{
		Weapon* weaponComp = inventory[i]->getComponent<Weapon>();
		if (weaponComp->getType() == ItemType::STICK)
			resource->getTexture("Stick")->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::PIPE)
			resource->getTexture("Crowbar")->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::AXE)
			resource->getTexture("Axe")->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::CROWBAR)
			resource->getTexture("Crowbar")->render(pRenderer, DestRect);
	}
	else if (inventory[i]->getComponent<FirstAid>())
	{
		resource->getTexture("Firstaid")->render(pRenderer, DestRect);
	}
	else if (inventory[i]->getComponent<Key>())
	{
		resource->getTexture("Key")->render(pRenderer, DestRect);
	}
}

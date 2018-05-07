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

void ItemContainer::saveToFile(ofstream& file)
{
	for (Entity* e : inventory) {
		file << e->getName() << endl;
		if (e->getComponent<Weapon>() != nullptr)
			file << e->getComponent<Weapon>()->getNumHits() << endl;
		if (e->getComponent<Key>() != nullptr)
			file << e->getComponent<Key>()->getDoorId() << endl;
	}
}

void ItemContainer::loadToFile(ifstream& file)
{
	inventory.clear();

	Entity* pEntity;
	string name;
	int numKey;
	int numHits;
	file >> name;
	while (!file.fail()) {
		pEntity = GameObjectFactory::Instance()->create(name);
		addItem(pEntity);
		if (pEntity->getComponent<Key>() != nullptr)
		{
			file >> numKey;
			pEntity->getComponent<Key>()->load(numKey);
		}
		else if (pEntity->getComponent<Weapon>() != nullptr)
		{
			file >> numHits;
			pEntity->getComponent<Weapon>()->setNumHits(numHits);
		}
		file >> name;
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
		resource->getTexture("insulationTape")->render(pRenderer, DestRect, &clip);
	}
	else if (inventory[i]->getComponent<Weapon>())
	{
		Weapon* weaponComp = inventory[i]->getComponent<Weapon>();
		if (weaponComp->getType() == ItemType::STICK)
			resource->getTexture("Stick")->render(pRenderer, DestRect, &clip);

		else if (weaponComp->getType() == ItemType::PIPE)
			resource->getTexture("Pipe")->render(pRenderer, DestRect, &clip);

		else if (weaponComp->getType() == ItemType::AXE)
			resource->getTexture("Axe")->render(pRenderer, DestRect, &clip);

		else if (weaponComp->getType() == ItemType::CROWBAR)
			resource->getTexture("Crowbar")->render(pRenderer, DestRect, &clip);
	}
	else if (inventory[i]->getComponent<FirstAid>())
	{
		resource->getTexture("Firstaid")->render(pRenderer, DestRect, &clip);
	}
	else if (inventory[i]->getComponent<Item>()->getType() == ItemType::ALCOHOL)
	{
		resource->getTexture("Alcohol")->render(pRenderer, DestRect, &clip);
	}
	else if (inventory[i]->getComponent<Key>())
	{
		resource->getTexture("Key")->render(pRenderer, DestRect, &clip);
	}
	else if (inventory[i]->getComponent<Item>()->getType() == ItemType::ACID)
	{
		resource->getTexture("Acid")->render(pRenderer, DestRect, &clip);
	}
	else if (inventory[i]->getComponent<Item>()->getType() == ItemType::ACIDCHEMICAL)
	{
		resource->getTexture("AcidChemical")->render(pRenderer, DestRect, &clip);
	}
	
}

void ItemContainer::renderSlotMark(SDL_Rect DestRect) {
	resource->getTexture("InventoryCursor")->render(pRenderer, DestRect);
}

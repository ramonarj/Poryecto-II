#include "Inventory.h"
#include "Game.h"
#include "FirstAid.h"


Inventory::Inventory()
{
	debug = false;
	equiped = nullptr;

	coord pos;
	pos.x = 32; pos.y = 306;
	for (int i = 0; i < InvTam; i++)
	{
		ObjPos.push_back(pos);
		pos.x += 61;
	}
	EquippedCoord.x = 265;
	EquippedCoord.y = 228;
}

Inventory::~Inventory()
{
}

void Inventory::update(Entity* e, Uint32 time)
{
}

void Inventory::handleInput(Entity* e, Uint32 time, const SDL_Event& event)
{
	
	if (event.type == SDL_MOUSEBUTTONDOWN && !clicked) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			int i = 0;
			while (i<inventory.size() && !clicked)
			{
				if ((event.button.x >= ObjPos[i].x && event.button.x <= ObjPos[i].x + 50)
					&& (event.button.y >= ObjPos[i].y && event.button.y <= ObjPos[i].y + 50))//EL 50 Es un numero provisional de prueba
				{ clicked = true; }

				slotClicked = i;
				i++;
			}
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP && clicked) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			clicked = false;
		}
	}
}

//Este m�todo coprueba por DuckTyping que objeto hay en cada parte del vector y lo pinta
void Inventory::render(Entity* e, Uint32 time)
{
	SDL_Rect dest = {0,0,600,600};
	//e->getGame()->getResources()->getImageTexture(Resources::Inventory)->render(e->getGame()->getRenderer(), dest);
	Game::Instance()->getResourceManager()->getTexture("Inventory")->render(e->getGame()->getRenderer(), dest);

	for (int i = 0; i < inventory.size(); i++)
	{
		if (i != slotClicked || !clicked) {
			SDL_Rect DestRect = { getItemPosX(i), getItemPosY(i), 50, 50 };
			renderItem(i, e, DestRect);
		}
		if (clicked)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			SDL_Rect DestRect = { x, y, 50, 50 };
			renderItem(slotClicked, e, DestRect);
		}
	}
	SDL_Rect DestRect = { EquippedCoord.x, EquippedCoord.y, 50, 50 };
	if (equiped->getComponent<Weapon>()->getType() == ItemType::Stick)
		equiped->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
	else if (equiped->getComponent<Weapon>()->getType() == ItemType::Pipe)
		equiped->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
	else if (equiped->getComponent<Weapon>()->getType() == ItemType::Ax)
		equiped->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
	else if (equiped->getComponent<Weapon>()->getType() == ItemType::Lever)
		equiped->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
}

void Inventory::renderItem(int i, Entity* e, SDL_Rect DestRect)
{
	if (inventory[i]->getComponent<InsulationTape>())
	{
		inventory[i]->getGame()->getResources()->getImageTexture(Resources::PruebaMedicKit)->render(e->getGame()->getRenderer(), DestRect);
	}
	else if (inventory[i]->getComponent<Weapon>())
	{
		if (inventory[i]->getComponent<Weapon>()->getType() == ItemType::Stick)
			inventory[i]->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
		else if (inventory[i]->getComponent<Weapon>()->getType() == ItemType::Pipe)
			inventory[i]->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
		else if (inventory[i]->getComponent<Weapon>()->getType() == ItemType::Ax)
			inventory[i]->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
		else if (inventory[i]->getComponent<Weapon>()->getType() == ItemType::Lever)
			inventory[i]->getGame()->getResources()->getImageTexture(Resources::Crowbar)->render(e->getGame()->getRenderer(), DestRect);
	}
	else if (inventory[i]->getComponent<FirstAid>())
	{
		inventory[i]->getGame()->getResources()->getImageTexture(Resources::PruebaMedicKit)->render(e->getGame()->getRenderer(), DestRect);
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

bool Inventory::fullInventory()
{
	if (inventory.size() >= InvTam) { return true; }
	else return false;
}



Entity * Inventory::currentWeapon()
{
	return equiped;
}





#include "Inventory.h"
#include "Game.h"
#include "FirstAid.h"


Inventory::Inventory()
{
	debug = false;
	equiped = nullptr;
	pRenderer = nullptr;
	resource = nullptr;
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
			while (i< int(inventory.size()) && !clicked)
			{
				if ((event.button.x >= slots[i].x && event.button.x <= slots[i].x + 50)
					&& (event.button.y >= slots[i].y && event.button.y <= slots[i].y + 50))//EL 50 Es un numero provisional de prueba
				{
					clicked = true;
				}

				slotClicked = i;
				i++;
			}
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP && clicked) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if ((event.button.x >= EquippedCoord.x && event.button.x <= EquippedCoord.x + 50)
				&& (event.button.y >= EquippedCoord.y && event.button.y <= EquippedCoord.y + 50))
			{
				equipWeapon(slotClicked);
			}
			clicked = false;
		}
	}
}

//Este m�todo coprueba por DuckTyping que objeto hay en cada parte del vector y lo pinta
void Inventory::render(Entity* e, Uint32 time)
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResources();

	int width = Game::Instance()->getWindowWidth();
	int height = Game::Instance()->getWindowHeight();

	int ancho = width - width / 10;
	int alto = height - height / 10;
	int posX = width / 2 - ancho / 2;
	int posY = height / 2 - alto / 2;

	SDL_Rect dest = { posX,posY, ancho,alto };
	Game::Instance()->getResourceManager()->getTexture("Inventory")->render(pRenderer, dest);

	//RENDERIZAMOS EL ARMA EQUIPADA
	if (equiped != nullptr) {
		Weapon* weaponComp = equiped->getComponent<Weapon>();
		SDL_Rect DestRect = { EquippedCoord.x, EquippedCoord.y, 50, 50 };

		if (weaponComp->getType() == ItemType::Stick)
			resource->getImageTexture(Resources::stick)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Pipe)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Ax)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Lever)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);
	}

	for (int i = 0; i < int(inventory.size()); i++)
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


}

void Inventory::renderItem(int i, Entity* e, SDL_Rect DestRect)
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResources();

	if (inventory[i]->getComponent<InsulationTape>())
	{
		resource->getImageTexture(Resources::PruebaMedicKit)->render(pRenderer, DestRect);
	}
	else if (inventory[i]->getComponent<Weapon>())
	{
		Weapon* weaponComp = inventory[i]->getComponent<Weapon>();
		if (weaponComp->getType() == ItemType::Stick)
			resource->getImageTexture(Resources::stick)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Pipe)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Ax)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Lever)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);
	}
	else if (inventory[i]->getComponent<FirstAid>())
	{
		resource->getImageTexture(Resources::PruebaMedicKit)->render(pRenderer, DestRect);
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
	while (!found && i < int(inventory.size()) && !empty())
	{
		if (ItemInPosition(i) == item) { found = true; }
	}
	return found;
}
//CHECK WHAT ITEM IS ON THE INDICATED POSITION
Entity * Inventory::ItemInPosition(int pos)
{
	if (pos < int(inventory.size()) && !empty()) { return inventory[pos]; }
	else return nullptr;
}

void Inventory::equipWeapon(int pos)
{
	if (inventory[pos]->getComponent<Weapon>()) {

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






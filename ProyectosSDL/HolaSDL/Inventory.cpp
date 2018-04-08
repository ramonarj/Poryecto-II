#include "Inventory.h"
#include "Game.h"
#include "FirstAid.h"
#include "Craft.h"

Inventory::Inventory()
{
	//InvTam = 4;
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
				if ((event.button.x >= Inventoryslots[i].x && event.button.x <= Inventoryslots[i].x + 50)
					&& (event.button.y >= Inventoryslots[i].y && event.button.y <= Inventoryslots[i].y + 50))//EL 50 Es un numero provisional de prueba //cambio
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
			//COMPROBAR SI SE HA SOLTADO EN LAAS COORDENADAS DEL ARMA EQUIPADA
			if ((event.button.x >= EquippedCoord.x && event.button.x <= EquippedCoord.x + 50)
				&& (event.button.y >= EquippedCoord.y && event.button.y <= EquippedCoord.y + 50)) //cambio
			{
				equipWeapon(slotClicked);
			}
			//COMPROBAR SI SE HA SOLTADO DENTRO DE LAS COORDENADAS DEL COFRE
			else if(chestMode){
				if (cofre == nullptr) { cofre = Game::Instance()->getEntityWithComponent<Chest>()->getComponent<Chest>(); }
					if ((event.button.x >= ChestSlots[0].x && event.button.x <= ChestSlots[cofre->getChestTam() - 1].x)
						&& (event.button.y >= ChestSlots[0].y && event.button.y <= ChestSlots[cofre->getChestTam() - 1].y))
					{
						if (!cofre->fullChest()) {
							cofre->addItem(inventory[slotClicked]);
							this->DeleteItem(slotClicked);
						}
					}
			}

			else if (craftMode) {
				if (craftWin == nullptr) { craftWin = Game::Instance()->getEntityWithComponent<Craft>()->getComponent<Craft>(); }
				if ((event.button.x >= craftWin->WepRepareSlot().x && event.button.x <= craftWin->WepRepareSlot().x + 50)//Cambiar
					&& (event.button.y >= craftWin->WepRepareSlot().y && event.button.y <= craftWin->WepRepareSlot().y + 50)
					&& inventory[slotClicked]->getComponent<Weapon>() && !craftWin->WepinSlot())
				{
					craftWin->setWep(inventory[slotClicked]);
					this->DeleteItem(slotClicked);
				}
					
				else if ((event.button.x >= craftWin->InsulationTapeRepareSlot().x && event.button.x <= craftWin->InsulationTapeRepareSlot().x + 50)//Cambiar
					&& (event.button.y >= craftWin->InsulationTapeRepareSlot().y && event.button.y <= craftWin->InsulationTapeRepareSlot().y + 50)
					&&inventory[slotClicked]->getComponent<Item>()->getType() == ItemType::INSULATIONTEPE && !craftWin->CintainSlot()) {
						craftWin->setCinta(inventory[slotClicked]);
						this->DeleteItem(slotClicked);
				}
				
			}
			clicked = false;
		}
	}
	
}

//Este m�todo coprueba por DuckTyping que objeto hay en cada parte del vector y lo pinta
void Inventory::render(Entity* e, Uint32 time)
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResourceManager();

	int width = Game::Instance()->getWindowWidth();
	int height = Game::Instance()->getWindowHeight();

	int ancho = width - width / 10;
	int alto = height - height / 10;
	int posX = width / 2 - ancho / 2;
	int posY = height / 2 - alto / 2;

	SDL_Rect dest = { posX,posY, ancho,alto };
	resource->getTexture("Inventory")->render(pRenderer, dest);

	//RENDERIZAMOS EL ARMA EQUIPADA
	if (equiped != nullptr) {
		Weapon* weaponComp = equiped->getComponent<Weapon>();
		SDL_Rect DestRect = { EquippedCoord.x, EquippedCoord.y, 50, 50 };

		if (weaponComp->getType() == ItemType::STICK)
			resource->getTexture("Stick")->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::PIPE)
			resource->getTexture("Crowbar")->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::AXE)
			resource->getTexture("Axe")->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::CROWBAR)
			resource->getTexture("Crowbar")->render(pRenderer, DestRect);
	}

	for (int i = 0; i < int(inventory.size()); i++)
	{
		if (i != slotClicked || !clicked) {
			SDL_Rect DestRect = { getItemInvPosX(i), getItemInvPosY(i), 50, 50 };
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


bool Inventory::addItem(Entity * item)
{
	bool alm = false;
	bool equip = false;
	if (equiped == nullptr)
	{
		Weapon* wep = item->getComponent<Weapon>();
		if (wep != nullptr) {
			equiped = item;
			equip = true;
			alm = true;
		}
	}
	if (!fullInventory() && !equip) {
		inventory.push_back(item);
		Key* k = item->getComponent<Key>();
		if (k != nullptr)
			keys.push_back(item);
		alm = true;
	}
	return alm;
}

//CHECK IF ITEM "item" IS ON THE INVENTORY
bool Inventory::checkItem(int item)
{
	int i = 0;
	bool found = false;
	if (debug) { return true; }

	while (!found && i < int(inventory.size()) && !empty())
	{
		if (ItemInPosition(i)->getComponent<Item>()->getType() == item) { found = true; }
		else i++;
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
	if (inventory.size() >= InventoryTam) { return true; }
	else return false;
}

void Inventory::objectCrafted(int a, int b)
{
	int i = 0;
	bool found = false;
	while (!found && i < int(inventory.size()) && !empty())
	{
		if (ItemInPosition(i)->getComponent<Item>()->getType() == a) { 
			found = true;
			inventory.erase(inventory.begin() + i);
		}
		else i++;
	}
	i = 0;
	found = false;
	while (!found && i < int(inventory.size()) && !empty())
	{
		if (ItemInPosition(i)->getComponent<Item>()->getType() == b) {
			found = true; 
			inventory.erase(inventory.begin() + i);
		}
		else i++;
	}
}



Entity * Inventory::currentWeapon()
{
	return equiped;
}






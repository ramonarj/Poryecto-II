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
	description_.addComponent(new TextNote(Game::Instance(), "ItemDescriptions/StickDescription.txt", 710, 510, nullptr));
}

Inventory::~Inventory()
{
	for (int i = 0; i < inventory.size(); i++){ if (inventory[i] != nullptr) delete inventory[i]; }
	for (int i = 0; i < keys.size(); i++) { if (keys[i] != nullptr) delete keys[i]; }
	if (equiped != nullptr) delete equiped;
	equiped = nullptr;
}

void Inventory::update(Entity* e, Uint32 time)
{
}

void Inventory::handleInput(Entity* e, Uint32 time, const SDL_Event& event)
{

	if (cofre == nullptr)
		cofre = Game::Instance()->getEntityWithComponent<Chest>()->getComponent<Chest>();
	if (craftWin == nullptr)
		craftWin = Game::Instance()->getEntityWithComponent<Craft>()->getComponent<Craft>();

	if ((event.type == SDL_MOUSEBUTTONDOWN && !clicked)) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			int i = 0;

			if ((event.button.x >= EquippedCoord.x && event.button.x <= EquippedCoord.x +slotWidth)
				&& (event.button.y >= EquippedCoord.y && event.button.y <= EquippedCoord.y + slotWidth))
			{
				equipedClicked = true;
				equipedLastClicked = true;
			}
			
			else {
				while (i< int(inventory.size()) && !clicked)
				{
					if ((event.button.x >= Inventoryslots[i].x && event.button.x <= Inventoryslots[i].x + slotWidth)
						&& (event.button.y >= Inventoryslots[i].y && event.button.y <= Inventoryslots[i].y + slotWidth))//EL 50 Es un numero provisional de prueba //cambio
					{
						clicked = true;
						equipedLastClicked = false;
					}

					slotClicked = i;
					i++;
				}
			}
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP && clicked) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			//COMPROBAR SI SE HA SOLTADO EN LAAS COORDENADAS DEL ARMA EQUIPADA
			if ((event.button.x >= EquippedCoord.x && event.button.x <= EquippedCoord.x + slotWidth)
				&& (event.button.y >= EquippedCoord.y && event.button.y <= EquippedCoord.y + slotWidth)) //cambio
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
				if ((event.button.x >= craftWin->WepRepareSlot().x && event.button.x <= craftWin->WepRepareSlot().x + slotWidth)//Cambiar
					&& (event.button.y >= craftWin->WepRepareSlot().y && event.button.y <= craftWin->WepRepareSlot().y + slotWidth)
					&& inventory[slotClicked]->getComponent<Weapon>())
				{
					craftWin->setWep(inventory[slotClicked]);
					this->DeleteItem(slotClicked);
				}
					
				else if ((event.button.x >= craftWin->InsulationTapeRepareSlot().x && event.button.x <= craftWin->InsulationTapeRepareSlot().x + slotWidth)//Cambiar
					&& (event.button.y >= craftWin->InsulationTapeRepareSlot().y && event.button.y <= craftWin->InsulationTapeRepareSlot().y + slotWidth)
					&&inventory[slotClicked]->getComponent<Item>()->getType() == ItemType::INSULATIONTEPE && !craftWin->CintainSlot()) {
						craftWin->setCinta(inventory[slotClicked]);
						this->DeleteItem(slotClicked);
				}
				
			}
			clicked = false;
		}
	}	

	else if (event.type == SDL_MOUSEBUTTONUP && equipedClicked) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			//COMPROBAR SI SE HA SOLTADO EN LAAS COORDENADAS DEL INVENTARIO
			if ((event.button.x >= Inventoryslots[0].x && event.button.x <= Inventoryslots[InventoryTam - 1].x + slotWidth)
				&& (event.button.y >= Inventoryslots[0].y && event.button.y <= Inventoryslots[InventoryTam - 1].y + slotWidth)) //cambio
			{
				if (!fullInventory())
				{
					inventory.push_back(equiped);
					equiped = nullptr;
					equipedLastClicked = false;
				}
			}

			//COMPROBAR SI SE HA SOLTADO DENTRO DE LAS COORDENADAS DEL COFRE
			else if (chestMode) {
				if (cofre == nullptr) { cofre = Game::Instance()->getEntityWithComponent<Chest>()->getComponent<Chest>(); }
				if ((event.button.x >= ChestSlots[0].x && event.button.x <= ChestSlots[cofre->getChestTam() - 1].x)
					&& (event.button.y >= ChestSlots[0].y && event.button.y <= ChestSlots[cofre->getChestTam() - 1].y))
				{
					if (!cofre->fullChest()) {
						cofre->addItem(equiped);
						equiped = nullptr;
					}
				}
			}
			equipedClicked = false;
		}
	}
}

//Este m�todo coprueba por DuckTyping que objeto hay en cada parte del vector y lo pinta
void Inventory::render(Entity* e, Uint32 time)
{
	
	if (pRenderer == nullptr) pRenderer = Game::Instance()->getRenderer();
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();

	if (!chestMode && !craftMode) {
		int width = Game::Instance()->getWindowWidth();
		int height = Game::Instance()->getWindowHeight();

		int ancho = width - width / 10;
		int alto = height - height / 10;
		int posX = width / 2 - ancho / 2;
		int posY = height / 2 - alto / 2;

		SDL_Rect dest = { posX,posY, ancho,alto };
		resource->getTexture("Inventory")->render(pRenderer, dest);
	}
	//RENDERIZAMOS EL ARMA EQUIPADA
	if (equiped != nullptr) {
		Weapon* weaponComp = equiped->getComponent<Weapon>();
		SDL_Rect DestRect;

		int x, y;
		SDL_GetMouseState(&x, &y);

		if(!equipedClicked)
		DestRect = { EquippedCoord.x - slotWidth/2 + 2, EquippedCoord.y - slotWidth / 2 -2, slotWidth*2, slotWidth*2 };	//DEBUG
		else  DestRect = { x - slotWidth/2, y - slotWidth / 2, slotWidth*2, slotWidth*2 };

		if (weaponComp->getType() == ItemType::STICK)
			resource->getTexture("Stick")->render(pRenderer, DestRect, &clip);

		else if (weaponComp->getType() == ItemType::PIPE)
			resource->getTexture("Crowbar")->render(pRenderer, DestRect, &clip);

		else if (weaponComp->getType() == ItemType::AXE)
			resource->getTexture("Axe")->render(pRenderer, DestRect, &clip);

		else if (weaponComp->getType() == ItemType::CROWBAR)
			resource->getTexture("Crowbar")->render(pRenderer, DestRect, &clip);
	}

	for (int i = 0; i < int(inventory.size()); i++)
	{
		if (i != slotClicked || !clicked) {
			SDL_Rect DestRect = { getItemInvPosX(i) - slotWidth / 2, getItemInvPosY(i) - slotWidth / 2, slotWidth*2, slotWidth*2 };
			renderItem(i, e, DestRect);
		}
		if (clicked)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			SDL_Rect DestRect = { x - slotWidth / 2, y - slotWidth / 2, slotWidth*2, slotWidth*2 };
			renderItem(slotClicked, e, DestRect);
		}
	}

	if (controllerActive && renderMark) {
		if (selectedSlot <= 3) {
			SDL_Rect DestRect = { Inventoryslots[selectedSlot].x-slotWidth/2+5, Inventoryslots[selectedSlot].y-slotWidth/2+3, slotWidth*2-8, slotWidth*2-8 };
			renderSlotMark(DestRect);
		}
		else {
			SDL_Rect DestRect = { EquippedCoord.x-slotWidth/2-5, EquippedCoord.y-slotWidth/2-10, slotWidth*2+16, slotWidth*2+16 };
			renderSlotMark(DestRect);
		}
	}


	if (controllerActive) {
		if (selectedSlot >= 0 && selectedSlot<getInventory().size()) {
			//if(getInventory()[selectedSlot] != nullptr)
				description_.getComponent<TextNote>()->changeString(getInventory()[selectedSlot]->getComponent<Item>()->getPath());
		}
		else if (selectedSlot == 4) {
			if (equiped != nullptr)
				description_.getComponent<TextNote>()->changeString(equiped->getComponent<Item>()->getPath());
		}
		else {
			description_.getComponent<TextNote>()->changeString("");
		}
	}
	else {
		if (equipedLastClicked) {
			if (equiped != nullptr) {
				Entity* b = equiped;
				Item* c = b->getComponent<Item>();
				description_.getComponent<TextNote>()->changeString(c->getPath());
			}
		}
		else if (slotClicked >= 0 && slotClicked < getInventory().size()) {
			Entity* b = getInventory()[slotClicked];
			Item* c = b->getComponent<Item>();
			description_.getComponent<TextNote>()->changeString(c->getPath());
		}
		else {
			description_.getComponent<TextNote>()->changeString("");
		}
	}

	description_.getComponent<TextNote>()->render(nullptr, time);
}

void Inventory::saveToFile(Entity* o)
{
	/*ofstream file;
	file.open(FOLDER + SAVE_FOLDER + "Inventory/inventory.pac");
	if (file.is_open())
	{
		for (Entity* e : inventory)
			file << e;
	}
	file.close();*/
}

void Inventory::loadToFile(Entity* o)
{
	/*ifstream file;
	file.open(FOLDER + SAVE_FOLDER + "Inventory/inventory.pac");

	//Vemos si existe el archivo
	if (file.is_open())
	{
	}

	file.close();*/
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

		equipedLastClicked = true;

	}
}

void Inventory::removeWeapon()
{
	if (!fullInventory() && equiped != nullptr) {
		addItem(equiped);
		equiped = nullptr;
	}
	else if (fullInventory() && equiped != nullptr) {
		int i = 0;
		bool found = false;
		Entity* aux;
		while (i < inventorySize() && !found) {

			 aux = ItemInPosition(i);
			if (aux->getComponent<Weapon>() != nullptr) {

				DeleteItem(i);
				addItem(equiped);
				equiped = aux;
				found = true;

				}
			i++;
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

void Inventory::moveMarkSlot(int a) {
	
	switch (selectedSlot)
	{
	case 0:
		switch (a)
		{
		case 2:
			selectedSlot = 1;
			break;
		case 3:
			selectedSlot = 2;
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (a)
		{
		case 3:
			selectedSlot = 3;
			break;
		case 4:
			selectedSlot = 0;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (a)
		{
		case 1:
			selectedSlot = 0;
			break;
		case 2:
			selectedSlot = 3;
			break;
		case 3:
			selectedSlot = 4;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (a)
		{
		case 1:
			selectedSlot = 1;
			break;
		case 3:
			selectedSlot = 4;
			break;
		case 4:
			selectedSlot = 2;
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (a)
		{
		case 1:
			selectedSlot = 2;
			break;
		case 2:
			selectedSlot = 3;
			break;
		case 4:
			selectedSlot = 2;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}



void Inventory::activeItem()
{
	if (selectedSlot <= 3) {
		Entity * aux;
		aux = ItemInPosition(selectedSlot);

		if (aux != nullptr) {

			if (aux->getComponent<Weapon>() != nullptr) {
				equipWeapon(selectedSlot);
			}
			else if (aux->getComponent<FirstAid>() != nullptr) {
				aux->getComponent<FirstAid>()->use(Game::Instance()->getEntityWithComponent<Player>(),aux);
			}
		}
	}
	else if (selectedSlot == 4)
		removeWeapon();
}

void Inventory::moveItem()
{

	if (cofre == nullptr)
		cofre = Game::Instance()->getEntityWithComponent<Chest>()->getComponent<Chest>();

	Entity* aux;
	if (selectedSlot < 4) {
		aux = ItemInPosition(selectedSlot);

		if (aux != nullptr) {

			if (!cofre->fullInventory())
			{
				cofre->addItem(aux);
				this->DeleteItem(selectedSlot);
			}
			else {
				Entity* auxInv = ItemInPosition(selectedSlot);	//Guardamos la entidad del inventario
				Entity* auxCofre = cofre->ItemInPosition(cofre->getSelectedSlot());
				DeleteItem(selectedSlot);	//La borramos
				cofre->DeleteItem(cofre->getSelectedSlot());
				cofre->addItem(auxCofre);					//Borramos la del cofre
				this->addItem(auxInv);						//Añadimos al cofre la del inventario
			}
		}
	}
	else if (selectedSlot == 4 && equiped!=nullptr) {
		
		aux = equiped;

		if (!cofre->fullInventory())
		{
			cofre->addItem(aux);
			equiped = nullptr;
		}
		else {
			Entity* auxCofre;// = cofre->ItemInPosition(cofre->getSelectedSlot());

			int i = 0;
			bool found = false;
			while (i < cofre->inventorySize() && !found) {

				auxCofre = cofre->getInventory()[i];

				if (auxCofre->getComponent<Weapon>() != nullptr) {

					equiped = auxCofre;		//Al encontrar un objeto en el cofre con componente arma, ponemos ese arma como la equipada
					cofre->DeleteItem(i);	//Borramos ese objeto del cofre
					cofre->addItem(aux);	//Añadimos al cofre el arma equipada guardada al principio en la variable auxiliar aux
					found = true;			//Salimos del bucle
				}
				i++;
			}
		}
	}
}

void Inventory::setToRepair()
{
	if (craftWin == nullptr) craftWin = Game::Instance()->getEntityWithComponent<Craft>()->getComponent<Craft>();
	if (selectedSlot < 4) {
		if (!craftWin->WepinSlot() || !craftWin->CintainSlot()) {

			Entity* aux = ItemInPosition(selectedSlot);
			if (aux != nullptr) {
				if (aux->getComponent<Weapon>() != nullptr)
				{
					craftWin->setWep(ItemInPosition(selectedSlot));
					DeleteItem(selectedSlot);
				}
				else if (aux->getComponent<InsulationTape>() != nullptr) {		//SEGUIR POR AQUI NO SE METE PRIMERO LA CINTA
					craftWin->setCinta(ItemInPosition(selectedSlot));
					DeleteItem(selectedSlot);
				}
			}
		}
	}
	else if (selectedSlot == 4) {
		if (equiped != nullptr) {
			craftWin->setWep(equiped);
			equiped = nullptr;
		}
	}
}

Entity * Inventory::currentWeapon()
{
	return equiped;
}

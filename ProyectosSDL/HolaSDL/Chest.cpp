#include "Chest.h"
#include "Game.h"
#include "Inventory.h"



Chest::Chest()
{
	//InvTam = 20;
	pRenderer = nullptr;
	resource = nullptr;
}


Chest::~Chest()
{
}

void Chest::update(Entity * e, Uint32 time)
{
}

void Chest::handleInput(Entity * e, Uint32 time, const SDL_Event & event)
{

	if (inv == nullptr)
		inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>();

	if (event.type == SDL_MOUSEBUTTONDOWN && !clicked) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			int i = 0;
			while (i< int(inventory.size()) && !clicked)
			{
				if ((event.button.x >= ChestSlots[i].x && event.button.x <= ChestSlots[i].x + slotWidth)
					&& (event.button.y >= ChestSlots[i].y && event.button.y <= ChestSlots[i].y + slotWidth))//EL 50 Es un numero provisional de prueba
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
			if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }
			if (event.button.x >= Inventoryslots[0].x && event.button.x <= Inventoryslots[inv->getInvTam() - 1].x + slotWidth &&
				event.button.y >= Inventoryslots[0].y && event.button.y <= Inventoryslots[inv->getInvTam() - 1].y + slotWidth)
			{
				if (!inv->fullInventory())
				{
					inv->addItem(inventory[slotClicked]);
					this->DeleteItem(slotClicked);
				}
			}
			clicked = false;
		}
	}
}

void Chest::render(Entity * e, Uint32 time)
{
	if (pRenderer == nullptr) pRenderer = Game::Instance()->getRenderer();
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();

	int width = Game::Instance()->getWindowWidth();
	int height = Game::Instance()->getWindowHeight();

	int ancho = width - width / 10;
	int alto = height - height / 10;
	int posX = 0 + (width / 10)/2;
	int posY = 0 + (height / 10)/2;

	SDL_Rect dest = { posX,posY, ancho,alto };
	resource->getTexture("Chest")->render(pRenderer, dest);

	for (int i = 0; i < int(inventory.size()); i++)
	{
		if (i != slotClicked || !clicked) {
			SDL_Rect DestRect = { getItemChestPosX(i), getItemChestPosY(i), slotWidth, slotWidth };
			renderItem(i, e, DestRect);
		}
			if (clicked)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				SDL_Rect DestRect = { x, y, slotWidth, slotWidth };
				renderItem(slotClicked, e, DestRect);
			}
	}

	if (controllerActive) {
		SDL_Rect DestRect;
		if(selectedSlot<5)
			DestRect = { ChestSlots[selectedSlot].x - slotWidth / 2 + 6, ChestSlots[selectedSlot].y - slotWidth / 2 + 3, slotWidth * 2 - 8, slotWidth * 2 - 8 };
		else if(selectedSlot<10)
			DestRect = { ChestSlots[selectedSlot].x - slotWidth / 2 + 6, ChestSlots[selectedSlot].y - slotWidth / 2, slotWidth * 2 - 8, slotWidth * 2 - 8 };
		else if (selectedSlot<15)
			DestRect = { ChestSlots[selectedSlot].x - slotWidth / 2 + 6, ChestSlots[selectedSlot].y - slotWidth / 2 - 3, slotWidth * 2 - 8, slotWidth * 2 - 8 };
		else if (selectedSlot<20)
			DestRect = { ChestSlots[selectedSlot].x - slotWidth / 2 + 6, ChestSlots[selectedSlot].y - slotWidth / 2 - 6, slotWidth * 2 - 8, slotWidth * 2 - 8 };

		renderSlotMark(DestRect);
	}

}

bool Chest::fullChest()
{
	return inventory.size() >= ChestTam;
}

bool Chest::addItem(Entity * item)
{
	bool alm = false;
	if (!fullChest()) { inventory.push_back(item); alm = true; }
	return alm;
}

bool Chest::checkItem(int item)
{
	int i = 0;
	bool found = false;
	while (!found && i < int(inventory.size()) && !empty())
	{
		if (ItemInPosition(i)->getComponent<Item>()->getType() == item) { found = true; }
	}
	return found;
}

Entity * Chest::ItemInPosition(int pos)
{
	if (pos < int(inventory.size()) && !empty()) { return inventory[pos]; }
	else return nullptr;
}

bool Chest::fullInventory()
{
	if (inventory.size() >= ChestTam) { return true; }
	else return false;
}

void Chest::moveItem()
{
	
	Entity* aux;
	aux = ItemInPosition(selectedSlot);

	if (aux != nullptr) {

		if (!inv->fullInventory())
		{
			inv->addItem(inventory[selectedSlot]);
			this->DeleteItem(selectedSlot);
		}
		else {
			//Entity* auxInv = &inv->ItemInPosition[inv->getSelectedSlot()];	//Guardamos la entidad del inventario
			//inv->DeleteItem(inv->getSelectedSlot());	//La borramos
			//inv->addItem(inventory[selectedSlot]);		//Añadimos la del cofre
			//this->DeleteItem(selectedSlot);				//Borramos la del cofre
			//this->addItem(auxInv);						//Añadimos al cofre la del inventario
		}
	}
}

void Chest::setSelectedSlot(int a)
{
	selectedSlot = a;
}

void Chest::moveMarkSlot(int a) {
	if (a == 1) //Arriba
	{
		if (selectedSlot > 4) {
			selectedSlot -= 5;
		}
	}
	else if (a == 2) //Derecha
	{
		if ((selectedSlot+1)%5 != 0) {
			selectedSlot++;
		}
	}
	else if	(a == 3) //Abajo
	{
		if (selectedSlot < 15) {
			selectedSlot += 5;
		}
	}
	else if	(a == 4) //Izquierda
	{
		if ((selectedSlot) % 5 != 0) {
			selectedSlot--;
		}
	}

}
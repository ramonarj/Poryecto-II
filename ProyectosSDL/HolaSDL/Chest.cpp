#include "Chest.h"
#include "Game.h"
#include "Inventory.h"


Chest::Chest()
{
	//InvTam = 20;
	pRenderer = nullptr;
	resource = nullptr;
	description_.addComponent(new TextNote(Game::Instance(), "ItemDescriptions/StickDescription.txt", 140, 510, nullptr));

	SDL_Color c { 0,255,100,255 };
	description_.getComponent<TextNote>()->setColor(c);
}


Chest::~Chest()
{
		for (int i = 0; i < inventory.size(); i++){ if (inventory[i] != nullptr) delete inventory[i]; }
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
	int posX = width / 2 - ancho / 2;
	int posY = height / 2 - alto / 2;

	SDL_Rect dest1 = { posX,posY, ancho,alto };
	resource->getTexture("Inventory")->render(pRenderer, dest1);

	ancho = width - width / 10;
	alto = height - height / 10;
	posX = 0 + (width / 10)/2;
	posY = 0 + (height / 10)/2;

	SDL_Rect dest = { posX,posY, ancho,alto };
	resource->getTexture("Chest")->render(pRenderer, dest);
	
	for (int i = 0; i < int(inventory.size()); i++)
	{
		if (i != slotClicked || !clicked) {
			SDL_Rect DestRect = { getItemChestPosX(i) - slotWidth / 2, getItemChestPosY(i) - slotWidth / 2, slotWidth*2 , slotWidth*2 };
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

	if (controllerActive) {
		if (selectedSlot >= 0 && selectedSlot < getInventory().size()) {
			description_.getComponent<TextNote>()->changeString(getInventory()[selectedSlot]->getComponent<Item>()->getPath());
		}
		else {
			description_.getComponent<TextNote>()->changeString("");
		}
	}
	else {
		if (slotClicked >= 0 && slotClicked<getInventory().size()) {
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

void Chest::saveToFile(Entity* o)
{
	ofstream file;
	file.open(FOLDER + SAVE_FOLDER + "Inventory/chest.pac");
	if (file.is_open())
	{
		ItemContainer::saveToFile(file);
	}
	file.close();
}

void Chest::loadToFile(Entity* o)
{
	ifstream file;
	file.open(FOLDER + SAVE_FOLDER + "Inventory/chest.pac");

	//Vemos si existe el archivo
	if (file.is_open())
	{
		ItemContainer::loadToFile(file);
	}

	file.close();
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
			//inv->addItem(inventory[selectedSlot]);		//A�adimos la del cofre
			//this->DeleteItem(selectedSlot);				//Borramos la del cofre
			//this->addItem(auxInv);						//A�adimos al cofre la del inventario
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
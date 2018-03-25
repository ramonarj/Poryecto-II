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
	if (event.type == SDL_MOUSEBUTTONDOWN && !clicked) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			int i = 0;
			while (i< int(inventory.size()) && !clicked)
			{
				if ((event.button.x >= ChestSlots[i].x && event.button.x <= ChestSlots[i].x + 50)
					&& (event.button.y >= ChestSlots[i].y && event.button.y <= ChestSlots[i].y + 50))//EL 50 Es un numero provisional de prueba
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
			if (event.button.x >= Inventoryslots[0].x && event.button.x <= Inventoryslots[inv->getInvTam() - 1].x &&
				event.button.y >= Inventoryslots[0].y && event.button.y <= Inventoryslots[inv->getInvTam() - 1].y)
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
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResourceManager();

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
			SDL_Rect DestRect = { getItemChestPosX(i), getItemChestPosY(i), 50, 50 };
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

bool Chest::fullChest()
{
	return inventory.size() >= ChestTam;
}

void Chest::addItem(Entity * item)
{
	if (!fullChest()) { inventory.push_back(item); }
}

bool Chest::checkItem(Entity * item)
{
	int i = 0;
	bool found = false;
	while (!found && i < int(inventory.size()) && !empty())
	{
		if (ItemInPosition(i) == item) { found = true; }
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

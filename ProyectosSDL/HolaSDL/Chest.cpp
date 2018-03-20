#include "Chest.h"
#include "Game.h"



Chest::Chest()
{
	InvTam = 20;
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
			while (i< int(chest.size()) && !clicked)
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
			clicked = false;
		}
	}
}

void Chest::render(Entity * e, Uint32 time)
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResources();

	int width = Game::Instance()->getWindowWidth();
	int height = Game::Instance()->getWindowHeight();

	int ancho = width - width / 10;
	int alto = height - height / 10;
	int posX = 0 + (width / 10)/2;
	int posY = 0 + (height / 10)/2;

	SDL_Rect dest = { posX,posY, ancho,alto };
	Game::Instance()->getResourceManager()->getTexture("Chest")->render(pRenderer, dest);

	for (int i = 0; i < int(chest.size()); i++)
	{
			SDL_Rect DestRect = { getItemChestPosX(i), getItemChestPosY(i), 50, 50 };
			renderItem(i, e, DestRect);
	}
}

bool Chest::fullChest()
{
	return chest.size() >= InvTam;
}

void Chest::addItem(Entity * item)
{
	if (!fullChest()) { chest.push_back(item); }
}

bool Chest::checkItem(Entity * item)
{
	int i = 0;
	bool found = false;
	while (!found && i < int(chest.size()) && !empty())
	{
		if (ItemInPosition(i) == item) { found = true; }
	}
	return found;
}

void Chest::renderItem(int i, Entity * e, SDL_Rect DestRect)
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResources();

	if (chest[i]->getComponent<InsulationTape>())
	{
		resource->getImageTexture(Resources::PruebaMedicKit)->render(pRenderer, DestRect);
	}
	else if (chest[i]->getComponent<Weapon>())
	{
		Weapon* weaponComp = chest[i]->getComponent<Weapon>();
		if (weaponComp->getType() == ItemType::Stick)
			resource->getImageTexture(Resources::stick)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Pipe)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Ax)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);

		else if (weaponComp->getType() == ItemType::Lever)
			resource->getImageTexture(Resources::Crowbar)->render(pRenderer, DestRect);
	}
	else if (chest[i]->getComponent<FirstAid>())
	{
		resource->getImageTexture(Resources::PruebaMedicKit)->render(pRenderer, DestRect);
	}
}

Entity * Chest::ItemInPosition(int pos)
{
	if (pos < int(chest.size()) && !empty()) { return chest[pos]; }
	else return nullptr;
}

bool Chest::fullInventory()
{
	if (chest.size() >= InvTam) { return true; }
	else return false;
}

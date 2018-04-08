#include "Craft.h"


Craft::Craft()
{
}


Craft::~Craft()
{
}

void Craft::update(Entity * e, Uint32 time)
{
}

void Craft::handleInput(Entity * e, Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

		if ((event.button.x >= RepareButton.x && event.button.x <= RepareButton.x + 200)
			&& (event.button.y >= RepareButton.y && event.button.y <= RepareButton.y + 150)) {
			if (Wep != nullptr && cinta != nullptr)
				repare();
		}
		else if ((event.button.x >= craftSlotsclick[0].x && event.button.x <= craftSlotsclick[0].x + craftSlotsclick[0].w)
			&& (event.button.y >= craftSlotsclick[0].y && event.button.y <= craftSlotsclick[0].y + craftSlotsclick[0].h)) {
			slotCraftClicked = 0;
		}
		else if ((event.button.x >= craftSlotsclick[1].x && event.button.x <= craftSlotsclick[1].x + craftSlotsclick[1].w)
			&& (event.button.y >= craftSlotsclick[1].y && event.button.y <= craftSlotsclick[1].y + craftSlotsclick[1].h)) {
			slotCraftClicked = 1;
		}
		else if ((event.button.x >= craftSlotsclick[2].x && event.button.x <= craftSlotsclick[2].x + craftSlotsclick[2].w)
			&& (event.button.y >= craftSlotsclick[2].y && event.button.y <= craftSlotsclick[2].y + craftSlotsclick[2].h)) {
			slotCraftClicked = 2;
		}
		else if ((event.button.x >= craftSlotsclick[3].x && event.button.x <= craftSlotsclick[3].x + craftSlotsclick[3].w)
			&& (event.button.y >= craftSlotsclick[3].y && event.button.y <= craftSlotsclick[3].y + craftSlotsclick[3].h)) {
			slotCraftClicked = 3;
		}
		else if ((event.button.x >= craftButton.x && event.button.x <= craftButton.x + craftButton.w)
			&& (event.button.y >= craftButton.y && event.button.y <= craftButton.y + craftButton.h)) {
			craft();
		}
	}
}

void Craft::render(Entity * e, Uint32 time)
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResourceManager();

	int width = Game::Instance()->getWindowWidth();
	int height = Game::Instance()->getWindowHeight();

	int ancho = width - width / 10;
	int alto = height - height / 10;
	int posX = 0 + (width / 10) / 2;
	int posY = 0 + (height / 10) / 2;

	SDL_Rect dest = { posX,posY, ancho,alto };
	resource->getTexture("Craft")->render(pRenderer, dest);

	renderItem(Wep, repareSlots[WeaponSlot]);
	renderItem(cinta, repareSlots[InsulationTapeSlot]);

	//RENDER DE LOS OBJETOS A CRAFTEAR
	resource->getTexture("Firstaid")->render(pRenderer, craftSlots[0]);
	resource->getTexture("acid")->render(pRenderer, craftSlots[1]);



}

void Craft::repare()
{
	Wep->getComponent<Weapon>()->repare(REPARE_VAR);
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }
	inv->addItem(Wep);
	Game::Instance()->getStateMachine()->currentState()->removeInteractibleOfStage(cinta);
	Wep = nullptr;
	cinta = nullptr;
}

void Craft::wepSwitch()
{
}

void Craft::renderItem(Entity* e, coord pos)
{	
	if (e != nullptr) {
		SDL_Rect DestRect = { pos.x, pos.y, 50, 50 };
		if (e->getComponent<InsulationTape>())
		{
			resource->getTexture("insulationTape")->render(pRenderer, DestRect);
		}
		else if (e->getComponent<Weapon>())
		{
			Weapon* weaponComp = e->getComponent<Weapon>();
			if (weaponComp->getType() == ItemType::STICK)
				resource->getTexture("Stick")->render(pRenderer, DestRect);

			else if (weaponComp->getType() == ItemType::PIPE)
				resource->getTexture("Crowbar")->render(pRenderer, DestRect);

			else if (weaponComp->getType() == ItemType::AXE)
				resource->getTexture("Axe")->render(pRenderer, DestRect);

			else if (weaponComp->getType() == ItemType::CROWBAR)
				resource->getTexture("Crowbar")->render(pRenderer, DestRect);
		}
		else if (e->getComponent<FirstAid>())
		{
			resource->getTexture("Firstaid")->render(pRenderer, DestRect);
		}
		else if (e->getComponent<Key>())
		{
			resource->getTexture("Key")->render(pRenderer, DestRect);
		}
	}
}

void Craft::craft()
{
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }
	switch (slotCraftClicked)
	{
	case 0:
		if (inv->checkItem(ItemType::BANDAGES) && inv->checkItem(ItemType::ALCOHOL) && !inv->fullInventory())
		{
			inv->objectCrafted(ItemType::BANDAGES, ItemType::ALCOHOL);
			Entity* e = new Entity(0, 0);
			e->addComponent(new FirstAid("Firstaid"));
			inv->addItem(e);
		}
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}

}

void Craft::setWep(Entity* e)
{
	Wep = e;
}

void Craft::setCinta(Entity* e)
{
	cinta = e;
}

void Craft::restoreObjects()
{
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>(); }

	if(Wep != nullptr) { 
		inv->addItem(Wep); 
		Wep = nullptr;
	}
	if (cinta != nullptr) { 
		inv->addItem(cinta); 
		cinta = nullptr;
	}
}

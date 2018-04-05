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
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if ((event.button.x >= RepareButton.x && event.button.x <= RepareButton.x + 200)//cambiar
				&& (event.button.y >= RepareButton.y && event.button.y <= RepareButton.y + 150))
				{
					repare();
				}			
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

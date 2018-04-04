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
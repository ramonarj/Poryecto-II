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
}

void Craft::repare()
{
}

void Craft::wepSwitch()
{
}

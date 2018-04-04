#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"
#include "Inventory.h"
#include "Game.h"

class Craft : public Component
{
public:
	Craft();
	~Craft();

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);

	Inventory* inv;
	Item* Wep;
	Item* cinta;
	
	SDL_Renderer* pRenderer = nullptr;
	ResourceManager* resource = nullptr;

	void repare();
	void wepSwitch();
	
};


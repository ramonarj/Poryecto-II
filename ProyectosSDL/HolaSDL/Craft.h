#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"
#include "ItemContainer.h"

enum repCoords { WeaponSlot, InsulationTapeSlot };

class Craft : public Component
{
public:
	Craft();
	~Craft();

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);

	Inventory* inv = nullptr;
	Entity* Wep = nullptr;
	Entity* cinta = nullptr;
	
	SDL_Renderer* pRenderer = nullptr;
	ResourceManager* resource = nullptr;

	void repare();
	void wepSwitch();
	void setWep(Entity* e);
	void setCinta(Entity* e);
	void restoreObjects();
	
	bool WepinSlot() { return Wep != nullptr; };
	bool CintainSlot() { return cinta != nullptr; };

	coord WepRepareSlot() { return repareSlots[WeaponSlot]; }
	coord InsulationTapeRepareSlot() { return repareSlots[InsulationTapeSlot]; }
	coord RepareButton = { 400, 490 };
private:
	coord repareSlots[2] = { { 158, 540 },{ 271, 540 } };
	void renderItem(Entity* e, coord pos);
	const int REPARE_VAR = 4;
};


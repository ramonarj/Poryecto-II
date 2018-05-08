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
	SDL_Rect craftSlots[4] = { { 129,100, 50,50 }, { 129,195, 50,50 }, { 129,290, 50,50 }, { 129,385, 50,50 } };
	SDL_Rect reparetSlotsRect[2] = { { 158, 540, 50,50 },{ 271, 540, 50,50 } };
	SDL_Rect craftSlotsclick[4] = { { 110, 83, 90, 90 },{ 110, 178, 90, 90 },{ 110, 273, 90, 90 },{ 110, 378, 90, 90 } };
	
	SDL_Rect craftButton = { 225,370, 370,90 };
	SDL_Rect repairButtonRect = { 400,485, 200,160 };

	//Controller
	void setActiveController(bool b) { controllerActive = b; };
	void moveMarkSlot(int a);
	void setSelectedSlot(int a) { selectedSlot = a; };
	void tryCraftingRepair();
	void retireBlock();
	void returnToInv();
	bool checkRepair();

	void renderSlotMark(SDL_Rect DestRect);
	bool getRepairButtonSelected() { return repairButtonSelected; };
	bool getCraftButtonSelected() { return craftButtonSelected; };
	void setRenderMark(bool a) { renderMark = a; };

private:
	coord repareSlots[2] = { { 158, 540 },{ 271, 540 } };
	void renderItem(Entity* e, coord pos);
	void craft();
	const int REPARE_VAR = 4;
	int slotCraftClicked = -1;

	bool craftButtonSelected = false;
	bool repairButtonSelected = false;

	bool controllerActive = false;
	int selectedSlot = 0;
	int slotWidth = 50;
	bool renderMark = false;

	SDL_Rect clip = RECT(0, 0, 20, 20);
	Entity description_ = Entity(20, 20);
};


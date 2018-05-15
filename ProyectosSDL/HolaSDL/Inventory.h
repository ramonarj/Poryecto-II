#pragma once
#include "ItemContainer.h"
#include <vector>
#include "Weapon.h"
#include "Chest.h"
#include <list>
#include "Key.h"


using namespace std;

class AnimationRenderObject;
class Craft;
class ControllerInputComponent;

class Inventory : public ItemContainer
{
public:
	Entity * equiped;
	Chest* cofre = nullptr;
	Craft* craftWin = nullptr;
	coord EquippedCoord = { 750, 343 };	
	const int InventoryTam = 4;

	Inventory();
	~Inventory();

	void setActiveController(bool b) { controllerActive = b; };
	void moveMarkSlot(int a);
	void setSelectedSlot(int a) { selectedSlot = a; };
	void useItem(int i);

protected:
	bool debug = false;
	
public:

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);
	virtual void saveToFile(Entity * o);
	virtual void loadToFile(Entity * o);

	bool addItem(Entity * item);

	//DEBUG METHODS
	void Debug_Mode_On() { debug = true; };
	void Debug_Mode_Off() { debug = false; };

	void destroyWeapon();

	virtual bool checkItem(int item);
	virtual bool checkIdemItems(int item, int repeat);
	virtual Entity* ItemInPosition(int pos);
	void equipWeapon(int pos);
	void removeWeapon();
	void removeKey(int numKey);
	virtual bool fullInventory();
	void setChestMode(bool a) { chestMode = a; }
	void setCraftMode(bool a) { craftMode = a; }
	void objectCrafted(int a, int b);
	//void renderItem(int i, Entity* e, SDL_Rect DestRect);

	Entity* currentWeapon();

	bool chestMode = false;
	bool craftMode = false;

	//GETS
	vector<Entity*> getKeys() { return keys; };
	int getInvTam() { return InventoryTam; };
	int getSelectedSlot() { return selectedSlot; };

	void activeItem();
	void moveItem();
	void setToRepair();
	void setRenderMark(bool a) { renderMark = a; }
	
private:
	vector<Entity*> keys;
	bool controllerActive = false;
	int selectedSlot = 0;
	bool equipedClicked = false;
	bool equipedLastClicked = false;
	bool renderMark = true;

	Entity description_ = Entity(20, 20);
	SDL_Rect clip = RECT(0, 0, 20, 20);

	Entity life = Entity(0, 0);

	double ritmoCardiaco1, ritmoCardiaco2, ritmoCardiaco3;	//1->lento, 2->medio, 3->rapido
	AnimationRenderObject* lifeGreen = nullptr;
	AnimationRenderObject* lifeRed = nullptr;
	AnimationRenderObject* lifeOrange = nullptr;

	SDL_Rect destE;

	ControllerInputComponent* controller_ = nullptr;
};




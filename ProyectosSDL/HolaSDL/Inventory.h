#pragma once
#include "ItemContainer.h"
#include <vector>
#include "Weapon.h"
#include "Chest.h"
#include <list>
#include "Key.h"

using namespace std;


class Inventory : public ItemContainer
{
public:
	Entity * equiped;
	Chest* cofre = nullptr;
	coord EquippedCoord = { 750, 343 };	
	const int InventoryTam = 4;

	Inventory();
	~Inventory();

protected:
	bool debug;

public:

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);

	bool addItem(Entity * item);

	//DEBUG METHODS
	void Debug_Mode_On() { debug = true; };
	void Debug_Mode_Off() { debug = false; };

	virtual bool checkItem(Entity* item);
	virtual Entity* ItemInPosition(int pos);
	void equipWeapon(int pos);
	virtual bool fullInventory();
	void setChestMode(bool a) { chestMode = a; }
	void setCraftMode(bool a) { craftMode = a; }
	//void renderItem(int i, Entity* e, SDL_Rect DestRect);

	Entity* currentWeapon();

	bool chestMode = false;
	bool craftMode = false;

	//GETS
	vector<Entity*> getKeys() { return keys; };
	int getInvTam() { return InventoryTam; };
	
private:
	vector<Entity*> keys;
};




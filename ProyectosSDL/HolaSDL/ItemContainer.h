#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"


using namespace std;

struct coord {
	int x;
	int y;
};


class ItemContainer : public Component
{
public:
	ItemContainer();
	~ItemContainer();

protected:

	//int InvTam;
	bool clicked = false;
	int slotClicked = -1;
	
	vector<Entity*> inventory;
	coord Inventoryslots[4] = { { 705, 100 },{ 800, 100 },{ 705,200 },{ 800,200 } };

	coord ChestSlots[20] = { { 135,100 },{ 230,100 },{ 325,100 },{ 420,100 },{ 515,100 },
							 { 135,200 },{ 230,200 },{ 325,200 },{ 420,200 },{ 515,200 },
							 { 135,300 },{ 230,300 },{ 325,300 },{ 420,300 },{ 515,300 },
							 { 135,400 },{ 230,400 },{ 325,400 },{ 420,400 },{ 515,400 } };

public:

	//ADD AND DELETE OBJECTS TO THE INVENTORY
	virtual bool addItem(Entity* item) = 0;
	void DeleteItem(int pos);
	void ClearInventory();

	//GETS
	int getItemInvPosX(int i) { return Inventoryslots[i].x; };
	int getItemInvPosY(int i) { return Inventoryslots[i].y; };
	int getItemChestPosX(int i) { return ChestSlots[i].x; };
	int getItemChestPosY(int i) { return ChestSlots[i].y; };
	
	int inventorySize() { return inventory.size(); };
	vector<Entity*> getInventory() { return inventory; };

	virtual void saveToFile(ofstream& file);
	virtual void loadToFile(ifstream& file);

protected:
	int slotWidth = 50;
	SDL_Renderer* pRenderer = nullptr;
	ResourceManager* resource = nullptr;

	//CHECK METHODS
	virtual bool checkItem(int item) = 0;
	virtual Entity* ItemInPosition(int pos) = 0;
	virtual bool fullInventory() = 0;
	bool empty();
	void renderItem(int i, Entity* e, SDL_Rect DestRect);

	void renderSlotMark(SDL_Rect DestRect);

	SDL_Rect clip = RECT(0, 0, 20, 20);

};


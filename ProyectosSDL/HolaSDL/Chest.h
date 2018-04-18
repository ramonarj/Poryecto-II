#pragma once
#include "ItemContainer.h"

class Inventory;
class Chest : public ItemContainer
{
public:
	Chest();
	~Chest();

	const int ChestTam = 20;
	Inventory* inv = nullptr;

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);
	
	bool fullChest();
	bool addItem(Entity * item);

	virtual bool checkItem(int item);
	virtual Entity* ItemInPosition(int pos);
	virtual bool fullInventory();

	//GETS
	int getChestTam() { return ChestTam; };

	//Controller
	void setActiveController(bool b) { controllerActive = b; };
	void moveMarkSlot(int a);
	void setSelectedSlot(int a);
	int getSelectedSlot() { return selectedSlot; };

	void moveItem();
	void setRenderMark(bool a) { renderMark = a; }
	
private:
	bool controllerActive = false;
	int selectedSlot = 0;
	bool renderMark = false;
};


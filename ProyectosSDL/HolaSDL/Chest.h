#pragma once
#include "ItemContainer.h"


class Chest : public ItemContainer
{
public:
	Chest();
	~Chest();

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);
	
	bool fullChest();
	void addItem(Entity * item);

	virtual bool checkItem(Entity* item);
	void renderItem(int i, Entity* e, SDL_Rect DestRect);
	virtual Entity* ItemInPosition(int pos);
	virtual bool fullInventory();
};


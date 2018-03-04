#pragma once
#include "LogicComponent.h"
#include <vector>
#include "Texture.h"
#include "Resources.h"
#include "Weapon.h"

using namespace std;

class ItemContainer : public LogicComponent, public RenderComponent
{
public:
	ItemContainer(int tam, Texture* Texture);
	~ItemContainer();

protected:
	int tam;
	vector<Entity*> inventory;
	Texture* texture;

public:

	//ADD AND DELETE OBJECTS TO THE INVENTORY
	virtual void addItem(Entity* item) = 0;
	void DeleteItem(int pos);
	void ClearInventory();

	//CHECK METHODS
	virtual bool checkItem(Entity* item) = 0;
	virtual Entity* ItemInPosition(int pos) = 0;
	//It returns false if the inventory isn't full
	bool fullInventory();
	bool empty();

};


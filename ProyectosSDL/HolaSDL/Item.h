#pragma once
#include "Interactible.h"
#include "Entity.h"
enum ItemType{ Stick, Lever, Pipe, Ax, Alcohol, Bandages, Firstaid, GenericChemical, AcidChemical, 
					Acid, Biocide, PiecePuzzle, Card, Key, Insulationtape, Photo };

class Item : public Interactible
{
public:
	Item(ItemType type) : type_(type) {};
	virtual ~Item();
	
	virtual void update(Entity* e, Uint32 time) {};
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event) {};
	virtual void render(Entity* e, Uint32 time) {};

	virtual void interact(); // Método para interactuar de los Items
	ItemType getType() { return type_; };
	virtual void useItem(Entity* e);
private:
	ItemType type_;
};


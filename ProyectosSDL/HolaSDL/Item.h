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

	// Método para interactuar de los Items
	virtual void interact(Entity* e, ItemContainer* ic);
	ItemType getType() { return type_; };
	
	// METODO PARA USAR UN ITEM (LOS ITEMS SE USAN DESDE EL INVENTARIO)
	virtual void use(Entity* e) {};
private:
	ItemType type_;
};


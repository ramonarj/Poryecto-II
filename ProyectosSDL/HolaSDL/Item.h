#pragma once
#include "Interactible.h"
enum ItemType{ Stick, Lever, Pipe, Ax, Alcohol, Bandages, FirstAid, GenericChemical, AcidChemical, 
					Acid, Biocide, PiecePuzzle, Card, Key, TapeInsulation, Photo };

class Item : public Interactible
{
public:
	Item(ItemType type) : type_(type) {};
	virtual ~Item();
	virtual void update();
	virtual void interact(); // Método para interactuar de los Items
private:
	ItemType type_;
};


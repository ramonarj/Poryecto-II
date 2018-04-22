#pragma once
#include "Interactible.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

enum ItemType{ STICK, CROWBAR, PIPE, AXE, ALCOHOL, BANDAGES, FIRSTAID, GENERICCHEMICAL, ACIDCHEMICAL,
					ACID, BIOCIDE, PIECEPUZZLE, CARD, KEY, INSULATIONTEPE, PHOTO, MASK };

class Item : public Interactible
{
public:
	Item(ItemType type, const string& filename, std::string interactMessage = "");
	virtual ~Item();

	virtual void update(Entity* e, Uint32 time) {};

	// M�todo para interactuar de los Items
	virtual void interact(Entity* e);
	ItemType getType() { return type_; };

	// METODO PARA USAR UN ITEM (LOS ITEMS SE USAN DESDE EL INVENTARIO)
	virtual void use(Entity* e, Entity* item);
	string getDescription() { return description; };
	string getPath() { return txtFilePath_; };

private:
	ItemType type_;
	string description;	//	descripcion que aparece en el inventario
	string txtFilePath_;
	bool loadDescription(const string& filename);	//	carga la descripcion del fichero DescriptionItems.txt
};
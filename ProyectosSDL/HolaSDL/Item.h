#pragma once
#include "Interactible.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "checkML.h"


using namespace std;

enum ItemType{ STICK, CROWBAR, PIPE, AXE, ALCOHOL, BANDAGES, FIRSTAID, GENERICCHEMICAL, ACIDCHEMICAL,
					ACID, BIOCIDE, PIECEPUZZLE, CARD, KEY, INSULATIONTEPE, PHOTO, MASK, CIRCUIT };

class Item : public Interactible
{
public:
	Item(ItemType type, const string& filename, std::string interactMessage = "");
	virtual ~Item();

	virtual void update(Entity* e, Uint32 time) {};

	// Metodo para interactuar de los Items
	virtual bool interact(Entity* e);
	ItemType getType() { return type_; };

	// METODO PARA USAR UN ITEM (LOS ITEMS SE USAN DESDE EL INVENTARIO)
	virtual void use(Entity* e, Entity* item);
	virtual string getDescription() { return description; };
	string getPath() { return txtFilePath_; };
	void setDescription(string s) { description = s; };

	void load(int num) { numFile_ = num; };

	virtual void saveToFile(Entity * o);
	virtual void loadToFile(Entity * o);

protected:
	int numFile_;
	string description;	//	descripcion que aparece en el inventario
	string txtFilePath_;

private:
	ItemType type_;
	bool loadDescription(const string& filename);	//	carga la descripcion del fichero DescriptionItems.txt
};
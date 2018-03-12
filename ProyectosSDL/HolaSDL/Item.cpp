#include "Item.h"
#include <iostream>
#include "ItemContainer.h"

Item::Item(ItemType type, const string& filename) : type_(type) {
	loadDescription(filename);
}

Item::~Item()
{
}

void Item::interact(Entity* e, ItemContainer* ic) {
	std::cout << "You interacted with: " << type_ << std::endl;
	//cuando coges un item desactivar los componentes de fisica
	ic->addItem(e);
}

bool Item::loadDescription(const string& filename) {
	ifstream archivo;
	stringstream ss,file;
	string line;

	file << "ItemDescriptions/" << filename << "Description.txt";
	archivo.open(file.str());

	while (getline(archivo, line))
	{
		ss << line << "\n";
	}
	description = ss.str();
	archivo.close();
	cout << endl << description << endl;
	return true;
}
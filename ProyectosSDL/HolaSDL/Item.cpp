#include "Item.h"
#include <iostream>
#include "ItemContainer.h"
#include "Game.h"

Item::Item(ItemType type, const string& filename, std::string interactMessage) : Interactible(interactMessage), type_(type) {
	loadDescription(filename);
}

Item::~Item()
{
}

void Item::use(Entity* e, Entity* item) { 
	PlayState::Instance()->removeEntity(item); 
}

void Item::saveToFile(Entity * o)
{
	ofstream file;
	file.open(SAVE_FOLDER + "Items/item" + o->getName() + to_string(numFile_) + ".pac");
	if (file.is_open())
	{
		file << o->isActive();
	}
	file.close();
}

void Item::loadToFile(Entity * o)
{
	ifstream file;
	file.open(SAVE_FOLDER + "Items/item" + o->getName() + to_string(numFile_) + ".pac");

	bool active;

	//Vemos si existe el archivo
	if (file.is_open())
	{
		file >> active;
		if (!active) 
			Game::Instance()->getStateMachine()->currentState()->removeInteractibleOfStage(o);
	}

	file.close();
}

void Item::interact(Entity* e) {
	if (dynamic_cast<PlayState*>(Game::Instance()->getStateMachine()
		->currentState())->inventory->getComponent<Inventory>()->addItem(e)) {
		Game::Instance()->getStateMachine()->currentState()->removeInteractibleOfStage(e);
	}

}

bool Item::loadDescription(const string& filename) {
	ifstream archivo;
	stringstream ss, file;
	string line;

	file << "ItemDescriptions/" << filename << "Description.txt";
	txtFilePath_ = "ItemDescriptions/" + filename + "Description.txt";
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
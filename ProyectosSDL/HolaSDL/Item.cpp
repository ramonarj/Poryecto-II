#include "Item.h"
#include <iostream>
#include "ItemContainer.h"
#include "Game.h"

Item::Item(ItemType type, const string& filename) : type_(type) {
	loadDescription(filename);
}

Item::~Item()
{
}

void Item::interact(Entity* e) {
	std::cout << "You interacted with: " << type_ << std::endl;
	
	if (dynamic_cast<PlayState*>(Game::Instance()->getStateMachine()
		->currentState())->inventory->getComponent<Inventory>()->addItem(e)) {
		Game::Instance()->getStateMachine()->currentState()->removeInteractibleOfStage(e);
		e->setActive(false);
	}

}

bool Item::loadDescription(const string& filename) {
	ifstream archivo;
	stringstream ss, file;
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
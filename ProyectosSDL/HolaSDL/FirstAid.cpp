#include "FirstAid.h"



FirstAid::FirstAid() : Item(ItemType::Firstaid)
{
}


FirstAid::~FirstAid()
{
}

void FirstAid::update(Entity* e, Uint32 time) {

}

void FirstAid::use(Entity* player) {
	if (player->getComponent<Player>() != nullptr) {
		std::cout << Item::getType() << " ha sido usado" << std::endl;
		//llamar al metodo de e de recargar vida
		//player->getComponent<Player>().
	}
}
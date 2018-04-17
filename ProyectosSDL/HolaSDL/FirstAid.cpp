#include "FirstAid.h"



FirstAid::FirstAid(const string& filename) : Item(ItemType::FIRSTAID,filename)
{
}


FirstAid::~FirstAid()
{
}

void FirstAid::use(Entity* player, Entity* item) {
	if (player->getComponent<Player>() != nullptr) {
		std::cout << Item::getType() << " ha sido usado" << std::endl;
		//llamar al metodo de e de recargar vida
		player->getComponent<Player>()->cure();
	}
	Item::use(player, item);
}
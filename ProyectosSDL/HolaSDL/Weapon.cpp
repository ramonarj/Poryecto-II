#include "Weapon.h"



Weapon::Weapon(ItemType type) : Item(type)
{
	weaponType(type);
}


Weapon::~Weapon()
{
}

void Weapon::weaponType(ItemType type) {
	switch (type)
	{
	case Stick:
		hits = 5;
	case Lever:
		hits = 10;
	case Pipe:
		hits = 15;
	case Ax:
		hits = 20;
		damage = 2;
		
	default:
		break;
	}
}

void Weapon::update() {

}
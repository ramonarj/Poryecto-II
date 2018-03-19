#include "Weapon.h"



Weapon::Weapon(ItemType type, const string& filename) : Item(type, filename)
{
	weaponInit(type);
	type_ = type;
}


Weapon::~Weapon()
{
}

void Weapon::weaponInit(ItemType type) {
	switch (type)
	{
	case Stick:
		maxHits_ = 5;
		break;
	case Lever:
		maxHits_ = 10;
		break;
	case Pipe:
		maxHits_ = 15;
		break;
	case Ax:
		maxHits_ = 20;
		damage_ = 2;
		break;
	default:
		maxHits_ = 1;
		damage_ = 1;
		break;
	}
	numHits_ = maxHits_;
}

void Weapon::attack() {

	numHits_--;
	std::cout << " has atacado, numHits = " << numHits_ << std::endl;

	if (numHits_ <= 0) {
		std::cout << "Arma destruida: " << this->getType() << std::endl;
		setEnabled(false); // no se como destuir el arma
	}
}

void Weapon::repair() {

	numHits_ += (int)repairIndex_*maxHits_;
	if (numHits_ > maxHits_) 
		numHits_ = maxHits_;
	std::cout << " arma reparada, numHits = " << numHits_ << std::endl;
}
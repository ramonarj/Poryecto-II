#include "Weapon.h"
#include "Game.h"


Weapon::Weapon(ItemType type, const string& filename, std::string interactMessage) : Item(type, filename, interactMessage)
{
	weaponInit(type);
	type_ = type;
}


Weapon::~Weapon()
{
}

void Weapon::update(Entity* e, Uint32 time) {
}

string Weapon::getDescription() {
	return Item::getDescription() +"Daño:" + to_string(damage_) + "               " + "Usos:" + to_string(numHits_) + "\n";
}

void Weapon::weaponInit(ItemType type) {
	switch (type)
	{
	case STICK:
		maxHits_ = 5;
		damage_ = 1;
		break;
	case CROWBAR:
		maxHits_ = 10;
		damage_ = 1;
		break;
	case PIPE:
		maxHits_ = 15;
		damage_ = 1;
		break;
	case AXE:
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
	//std::cout << " has atacado, numHits = " << numHits_ << std::endl;
	
	if (numHits_ <= 0) {
		//std::cout << "Arma destruida: " << this->getType() << std::endl;
		setEnabled(false);
		Entity* inv = Game::Instance()->getEntityWithComponent<Inventory>();
		inv->getComponent<Inventory>()->destroyWeapon();
		//cout << "hola";
	}
}

void Weapon::repare(int a)
{
	numHits_ += a;
	if (numHits_ > maxHits_)
		numHits_ = maxHits_;
}
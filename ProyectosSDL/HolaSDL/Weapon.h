#pragma once
#include "Item.h"
#include "InsulationTape.h"

class Weapon : public Item
{
	friend class InsulationTape;
public:
	Weapon(ItemType type);
	~Weapon();
	void attack(); // Resta 1 al numero de golpes que tiene el arma
private:
	int damage_;
	int numHits_;
	int maxHits_;
	double repairIndex_ = 0.6;

	void repair();	// Repara el arma
	void weaponInit(ItemType type);	// Metodo para inicializar el arma
};


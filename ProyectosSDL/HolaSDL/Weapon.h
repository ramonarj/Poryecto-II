#pragma once
#include "Item.h"
#include "InsulationTape.h"

class Weapon : public Item
{
	friend class InsulationTape;
public:
	Weapon(ItemType type, const string& filename);
	~Weapon();
	void attack(); // Resta 1 al numero de golpes que tiene el arma
	void repare(int a);
	int getTypeStr() { return (type_); };
private:
	int damage_;
	int numHits_;
	int maxHits_;
	double repairIndex_ = 0.6;
	ItemType type_;

	void repair();	// Repara el arma
	void weaponInit(ItemType type);	// Metodo para inicializar el arma
};


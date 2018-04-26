#pragma once
#include "Item.h"
#include "InsulationTape.h"

class Weapon : public Item
{
	friend class InsulationTape;
public:
	Weapon(ItemType type, const string& filename, std::string interactMessage = "");
	~Weapon();
	void attack(); // Resta 1 al numero de golpes que tiene el arma
	void repare(int a);
	int getTypeStr() { return (type_); };
	int getNumHits() { return numHits_; };
	void setNumHits(int num) { numHits_ = num; };
private:
	int damage_;
	int numHits_;
	int maxHits_;
	double repairIndex_ = 0.6;
	ItemType type_;

	void repair();	// Repara el arma
	void weaponInit(ItemType type);	// Metodo para inicializar el arma
};


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
	int getDamage() { return damage_; };
	int getTypeStr() { return (type_); };
	int getNumHits() { return numHits_; };
	void setNumHits(int num) { numHits_ = num; };
	virtual void update(Entity* e, Uint32 time);
private:
	int damage_;
	int numHits_;
	int maxHits_;
	double repairIndex_ = 0.6;
	ItemType type_;
	string initialDescr;

	void repair();	// Repara el arma
	void weaponInit(ItemType type);	// Metodo para inicializar el arma
	bool saveDescription();
};


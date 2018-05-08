#pragma once
#include "Component.h"
#include "Entity.h"

class Character: public Component
{
public:
	Character();
	void takeDamage(int i);
	bool isAlive() { return life > 0; };
	void setAlive() { life = maxLife_; };
	void setDie() { life = 0; };
	int getDamage() { return damage; };
	bool getAttacking() { return attacking; };
	void setAttacking(bool flag) { attacking = flag; };

	bool getKnockBack() { return knockBack_; };
	void setKnockBack(bool b) { knockBack_ = b; };
	Uint32 getKnockBackOn() { return knockBackOn_; };
	void setKnockBackOn() { knockBackOn_ = SDL_GetTicks(); };

	void load(int l, int d);
	void lif() { cout << life << endl; };

	virtual void update(Entity* o, Uint32 time);
	virtual void saveToFile();
	virtual void loadToFile(ifstream& file);
	virtual ~Character();

protected:
	int life, maxLife_;
	int damage;
	bool attacking = false;
	void move(Entity*o);
	void knockBack(Entity*o, Vector2D desplazamiento);
	void knockBack(Entity * o, Entity * own, double push);

private:
	bool knockBack_;
	Uint32 knockBackOn_;
	Uint32 knockBackTime_;
};


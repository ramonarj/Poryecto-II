#pragma once
#include "Character.h"
#include "Camera.h"

class Player :
	public Character
{
public:
	Player();

	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);

	int getLife() { return life; };
	void cure();
	void setWeaponId(int id) { WeaponId = id; };
	int getWeaponId() { return WeaponId; };

	virtual ~Player();
private:
	virtual void move(Entity* o);

	double cureIndex_ = 0.6;
	int WeaponId;
};


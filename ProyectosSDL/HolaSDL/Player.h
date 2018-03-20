#pragma once
#include "Character.h"
#include "Camera.h"
class Player :
	public Character
{
public:
	Player();
	Player(int life, int damage);

	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);

	int getLife() { return life; };
	void cure();
	void setWeaponId(int id) { WeaponId = id; };
	int getWeaponId() { return WeaponId; };

	void setDoorCollision(bool b) { doorCollision = b; };
	bool getDoorCollision() { return doorCollision; };

	void setTeleport(bool b) { teleport = b; };
	bool getTeleport() { return teleport; };

	virtual ~Player();
private:
	virtual void move(Entity* o);

	int maxLife_;
	double cureIndex_ = 0.6;
	int WeaponId;

	bool doorCollision;
	bool teleport;
};


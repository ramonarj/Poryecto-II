#pragma once
#include "Character.h"
#include "Camera.h"
#include "FadeManager.h"

class Player :
	public Character
{
public:
	Player();

	virtual void update(Entity* o, Uint32 time);
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);
	virtual void saveToFile(Entity* o);
	virtual void loadToFile(Entity* o);

	int getLife() { return life; };
	int getMaxLife() { return maxLife_; };
	void cure();
	void setWeaponId(int id) { WeaponId = id; };
	int getWeaponId() { return WeaponId; };
	bool getAwakening() { return awakening_; };
	void setAwakening(bool awk) { awakening_ = awk; };

	bool getCoolDown() { return coolDown_; };
	void startCoolDown();
	void coolDownAttack(Uint32 time);

	bool getInvincible() { return invincible_; };
	void startInvincible();
	void invincible(Entity* o, Uint32 time);

	bool getTeleport() { return teleport_; };
	void startTeleport(Entity* e, int door, string ori);
	int getNumDoor() { return numDoorToTeleport_; };
	string getOriDoor() { return oriDoorToTeleport_; };
	Entity* getDoorToTeleport() { return doorToTeleport_; };

	bool getPunch() { return punch; };
	void setPunch(bool p) { punch = p; };

	virtual ~Player();
private:
	virtual void move(Entity* o);

	bool punch = false;
	bool awakening_ = true;
	double cureIndex_ = 0.6;
	int WeaponId;

	string filename;

	//Cooldown del ataque
	bool coolDown_;
	Uint32 coolDownOn_;
	Uint32 coolDownTime_;

	//Invencibilidad por unos segundos
	bool invincible_;
	Uint32 invincibleOn_;
	Uint32 invincibleOnOff_;
	Uint32 invincibleTime_;

	//Teleport entre habitaciones
	bool teleport_;
	int numDoorToTeleport_;
	string oriDoorToTeleport_;
	Entity* doorToTeleport_;
};


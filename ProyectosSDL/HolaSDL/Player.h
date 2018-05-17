#pragma once
#include "Character.h"
#include "Camera.h"
#include "FadeManager.h"
#include "checkML.h"


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

	//Cooldown del ataque
	bool getCoolDown() { return coolDown_; };
	void startCoolDown();
	void coolDownAttack(Uint32 time);

	//Invencibilidad por unos segundos
	bool getInvincible() { return invincible_; };
	void setInvincible(bool b) { invincible_ = b; };
	void startInvincible();
	void invincible(Entity* o, Uint32 time);

	//Teleport entre habitaciones
	void setTeleport(bool b) { teleport_ = b; };
	bool getTeleport() { return teleport_; };
	void startTeleport(Entity* e, int door, string ori);
	int getNumDoor() { return numDoorToTeleport_; };
	string getOriDoor() { return oriDoorToTeleport_; };
	Entity* getDoorToTeleport() { return doorToTeleport_; };

	//Teleport a la ultima SR o a la habitacion inicial cuando mueres
	void setLastSRPos(Vector2D pos) { lastSRpos_ = pos; };
	Vector2D getLastSRPos() { return lastSRpos_; };

	bool getPunch() { return punch; };
	void setPunch(bool p) { punch = p; };

	virtual ~Player();
private:
	virtual void move(Entity* o);
	
	bool punch = false;
	bool awakening_ = true;
	bool deadSound = false;
	double cureIndex_ = 0.6;
	int WeaponId;

	string filename;

	//DoorSound
	Uint32 SoundTime = 0;
	bool sound = false;

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

	//Teleport a la ultima SR o a la habitacion inicial cuando mueres
	Vector2D lastSRpos_;
};


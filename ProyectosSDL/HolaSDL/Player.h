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
	virtual void saveToFile(Entity* o);
	virtual void loadToFile(Entity* o);

	int getLife() { return life; };
	void cure();
	void setWeaponId(int id) { WeaponId = id; };
	int getWeaponId() { return WeaponId; };
	bool getAwakening() { return awakening_; };
	void setAwakening(bool awk) { awakening_ = awk; };

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
};


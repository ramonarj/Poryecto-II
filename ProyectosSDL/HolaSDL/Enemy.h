#pragma once
#include "Character.h"
#include "Player.h"
#include "Collisions.h"

const int DEFAULT_RANGE = 400;
const int DEFAULT_KNOCKBACK = 10;
const int ALCANCE = 20;
const int COOLDOWN = 40;


class Enemy :
	public Character
{
public:
	Enemy();

	void addPlayer(Entity* player) { this->player = player; };
	void setVel(int vel) { this->velMag = vel; };
	void revive();
	void setResurrecting(bool value) { resurecting = value; };
	void punch(Entity* o);

	bool getResurrecting() { return resurecting; };
	bool getDead() { return dead; };

	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 tiDSme);

	void load(int numEnemy);

	virtual ~Enemy();
private:
	Entity* player;
	Entity* myself = nullptr;

	Vector2D chaseVector_;

	int numEnemy_;
	int rango;
	int velMag;
	int relaxTime;
	bool reloading;
	bool dead;
	bool resurecting=false;

	double push;

	Uint32 deadOn_;
	Uint32 deadTime_;

	virtual void move(Entity* o);
	bool playerInRange(Entity * o);
	void checkCollisions(Entity * o, Vector2D chaseVector);

	void bringMeToLife(Uint32 time);
};


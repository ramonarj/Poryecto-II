#pragma once
#include "Character.h"
#include "Player.h"
#include "Collisions.h"

const int DEFAULT_RANGE = 400;
const int DEFAULT_KNOCKBACK = 10;
const int ALCANCE = 20;
const int COOLDOWN = 15;


class Enemy :
	public Character
{
public:
	Enemy();
	Enemy(Vector2D vel);
	Enemy(Entity* player, int life, int damage, int rango=DEFAULT_RANGE);

	void addPlayer(Entity* player) { this->player = player; };
	void setVel(int vel) { this->velMag = vel; };

	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 tiDSme);

	virtual ~Enemy();
private:
	Entity* player;

	int rango;
	int velMag;
	int relaxTime;
	bool reloading;

	virtual void move(Entity* o);
	bool playerInRange(Entity * o);
	void checkCollisions(Entity * o, Vector2D chaseVector);
};


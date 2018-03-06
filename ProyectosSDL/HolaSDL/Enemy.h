#pragma once
#include "Character.h"
#include "Player.h"
#include "Entity.h"
class Enemy :
	public Character
{
public:
	Enemy();
	Enemy(Entity* player, int life, int damage);

	void addPlayer(Entity* player) { this->player = player; };

	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time);

	virtual ~Enemy();
private:
	Entity* player;

	virtual void move(Entity* o);
};


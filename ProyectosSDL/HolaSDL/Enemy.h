#pragma once
#include "Character.h"
#include "Player.h"
class Enemy :
	public Character
{
public:
	Enemy();
	Enemy(Player* player, int posX, int posY);

	virtual void update(Entity* o, Uint32 time);
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);

	virtual ~Enemy();
private:
	Player* player;
};


#pragma once
#include "Character.h"
#include "Player.h"
class Enemy :
	public Character
{
public:
	Enemy();
	Enemy(Player* player);

	virtual void update(GameObject* o, Uint32 time);
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	virtual void render(GameObject* o, Uint32 time);

	virtual ~Enemy();
private:
	Player* player;
};


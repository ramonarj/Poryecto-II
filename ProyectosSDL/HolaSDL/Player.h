#pragma once
#include "Character.h"
class Player :
	public Character
{
public:
	Player();
	Player(int life);

	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* o, Uint32 time);

	int getLife() { return life; };

	virtual ~Player();
private:
	virtual void move(Entity* o);
};


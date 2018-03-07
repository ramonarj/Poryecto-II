#pragma once
#include "Character.h"
#include "Entity.h"
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
	virtual void move(Entity* o);

	virtual ~Player();
private:
	
	int maxLife_;
	double cureIndex_ = 0.6;
};


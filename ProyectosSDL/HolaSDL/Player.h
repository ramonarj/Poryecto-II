#pragma once
#include "Character.h"
#include "Camera.h"
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

	virtual ~Player();
private:
	virtual void move(Entity* o);
	int maxLife_;
	double cureIndex_ = 0.6;
};


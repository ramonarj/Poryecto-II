#pragma once
#include "Character.h"
#include "Player.h"
class Enemy :
	public Character
{
public:
	Enemy();
	Enemy(Player* player);
	virtual ~Enemy();
	void update();
private:
	Player* player;
};


#pragma once
#include "Character.h"
#include "Player.h"
class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
private:
	Player* player;
};


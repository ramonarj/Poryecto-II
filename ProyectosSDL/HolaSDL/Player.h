#pragma once
#include "Character.h"
class Player :
	public Character
{
public:
	Player();
	virtual void update(GameObject* o, Uint32 time);
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	virtual void render(GameObject* o, Uint32 time);

	virtual ~Player();
};


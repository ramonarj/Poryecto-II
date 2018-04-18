#pragma once
#include "checkML.h"
#include "Component.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"

class PlayerLight {
public:
	PlayerLight();
	~PlayerLight();
	void render(Entity* o, Uint32 time);

private:
	bool horizontal_; //True = Horizontal, False = Vertical
	bool flipped_;
	Entity* player_;
	Texture* shadowH_;
	Texture* shadowV_;
	Texture* shadow_;
	SDL_Texture* sdlShadow;
	string currentDirection;
	string lastDirection;

	double currentAgl_;
	double destAgl_;
};


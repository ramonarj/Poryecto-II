#pragma once
#include "checkML.h"
#include "Component.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"

class PlayerLight :	public Component {
public:
	PlayerLight();
	~PlayerLight();
	virtual void render(Entity* o, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);

private:
	bool lightsOn_;
	bool horizontal_; //True = Horizontal, False = Vertical
	bool flipped_;
	Entity* player_;
	Texture* shadowH_;
	Texture* shadowV_;
};


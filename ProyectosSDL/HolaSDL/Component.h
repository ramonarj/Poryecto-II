#pragma once

#include "SDLGame.h"
#include "GameObject.h"

using namespace std;

class Entity;

class Component {

private:
	bool enabled_;

public:
	void setEnabled(bool enabled) { enabled_ = enabled; };
	bool isEnabled() { return enabled_; };
	Component();
	virtual ~Component();

	virtual void update(Entity* e, Uint32 time) {};
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event) {};
	virtual void render(Entity* e, Uint32 time) {};
	virtual void saveGame() {};
	virtual void loadGame() {};
};
#pragma once
#include "GameState.h"
class CreditsState : public GameState {
public:
	CreditsState();
	~CreditsState();
	virtual void startState();
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};


#pragma once
#include "GameState.h"
#include "checkML.h"


class CreditsState : public GameState {
private:
	float targetTime;
public:
	CreditsState();
	~CreditsState();
	virtual void startState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};


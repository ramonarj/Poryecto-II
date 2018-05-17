#pragma once
#include "GameState.h"
#include "checkML.h"


class PauseState : public GameState {

public:
	PauseState();
	~PauseState();
	virtual void startState();
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);

};

typedef PauseState PauseState;
#pragma once
#include "GameState.h"
#include "checkML.h"
#include "PauseControllerInput.h"

class PauseState : public GameState {

public:
	PauseState();
	~PauseState();
	vector<Entity*> botones;
	PauseControllerInput* controller_ = nullptr;
	int actualButton = 0;

	virtual void startState();
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);

	void update(Uint32 time);

	void moveButton(int a);
	void pressButton();
};

typedef PauseState PauseState;
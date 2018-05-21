#pragma once
#include "BaseControllerInput.h"


class PauseState;

class PauseControllerInput :
	public BaseControllerInput
{
public:
	PauseControllerInput(PauseState* h);
	virtual ~PauseControllerInput();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);

private:
	bool joystickMoved = true;
	int slot = 0;
	PauseState* state_ = nullptr;

	bool buttonPressed = false;
};


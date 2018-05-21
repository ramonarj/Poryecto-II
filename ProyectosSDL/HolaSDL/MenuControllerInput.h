#pragma once
#include "BaseControllerInput.h"

class MenuState;

class MenuControllerInput :
	public BaseControllerInput
{
public:
	MenuControllerInput(MenuState* h);
	virtual ~MenuControllerInput();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);

private:
	bool joystickMoved = true;
	int slot = 0;
	MenuState* state_ = nullptr;
};


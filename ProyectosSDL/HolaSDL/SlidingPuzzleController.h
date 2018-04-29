#pragma once
#include "BaseControllerInput.h"
#include "SlidingPuzzleComponent.h"

class SlidingPuzzleController :
	public BaseControllerInput
{
public:
	SlidingPuzzleController();
	virtual ~SlidingPuzzleController();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);

private:
	bool joystickMoved = true;
	int slot = 0;
	SlidingPuzzleComponent* puzll_ = nullptr;
};


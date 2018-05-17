#pragma once
#include "BaseControllerInput.h"
#include "OrderPuzzleComponent.h"
#include "checkML.h"


class OrderPuzzleController :
	public BaseControllerInput
{
public:
	OrderPuzzleController();
	virtual ~OrderPuzzleController();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);

private:
	bool joystickMoved = true;
	int slot = 0;
	OrderPuzzleComponent* puzll_ = nullptr;
};


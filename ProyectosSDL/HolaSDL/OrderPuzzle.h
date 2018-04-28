#pragma once
#include "GameState.h"
#include "OrderPuzzleComponent.h"

class OrderPuzzle : public GameState
{
private:
	OrderPuzzle();
	static unique_ptr<OrderPuzzle> s_pInstance;
public:
	~OrderPuzzle();

	static OrderPuzzle* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new OrderPuzzle());
		return s_pInstance.get();
	}

	virtual void startState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};

typedef OrderPuzzle OrderPuzzle;
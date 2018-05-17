#pragma once
#include "GameState.h"
#include "OrderPuzzleComponent.h"
#include "OrderPuzzleController.h"

class OrderPuzzle : public GameState
{
private:
	OrderPuzzle();
	static OrderPuzzle* s_pInstance;
	bool pop_ = false;

public:
	~OrderPuzzle();

	static OrderPuzzle* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new OrderPuzzle();
		return s_pInstance;
	}

	virtual void startState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
	virtual void resetSingleton() { s_pInstance = nullptr; };

	void setPop(bool b) { pop_ = b; };
	bool getPop() { return pop_; };
};

typedef OrderPuzzle OrderPuzzle;
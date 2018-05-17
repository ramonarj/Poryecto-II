#pragma once

#include "GameState.h"
#include "checkML.h"

#include <stack>

using namespace std;

class GameStateMachine {

private:
	stack<GameState*> states;
	int statesToPop;

	GameState* changeState_ = nullptr;
	GameState* pushState_ = nullptr;
public:
	GameStateMachine();
	~GameStateMachine();

	void popState();
	void popStateSafe();
	int getStatesToPop() { return statesToPop; };
	void pushState(GameState* state);
	void changeState(GameState* state);
	int size();
	bool pushStateTick();
	bool changeStateTick();
	bool empty() { return states.empty(); };
	GameState* currentState() { return states.top(); };
};


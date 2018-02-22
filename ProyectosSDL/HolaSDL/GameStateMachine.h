#pragma once
#include "GameState.h"
#include <stack>

using namespace std;

class GameStateMachine {

private:
	stack<GameState*> states;

public:
	GameStateMachine();
	~GameStateMachine();
	void popState();
	void pushState(GameState* state) { states.push(state); };
	void changeState(GameState* state);
	bool empty() { return states.empty(); };
	GameState* currentState() { return states.top(); };
};

